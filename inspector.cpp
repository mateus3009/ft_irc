#include <netdb.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <errno.h>
#include <sstream>

int get_socket(char *host, char *port)
{
    struct addrinfo hints, *res, *p;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = host == NULL ? AI_PASSIVE : 0;

    status = getaddrinfo(host, port, &hints, &res);
    if (status < 0)
    {
        std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
        return (-1);
    }

    int socketfd;
    const int yes = 1;
    for (p = res; p != NULL; p = p->ai_next)
    {
        socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socketfd < 0)
        {
            std::cerr << "socket: " << strerror(errno) << std::endl;
            continue ;
        }

        if (host != NULL)
        {
            if (connect(socketfd, p->ai_addr, p->ai_addrlen) < 0)
            {
                close(socketfd);
                std::cerr << "connect: " << strerror(errno) << std::endl;
                continue ;
            }
            break ;
        }

        if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
        {
            close(socketfd);
            std::cerr << "setsockopt: " << strerror(errno) << std::endl;
            continue ;
        }

        if (bind(socketfd, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(socketfd);
            std::cerr << "bind: " << strerror(errno) << std::endl;
            continue ;
        }

        if (listen(socketfd, 10) < 0)
        {
            close(socketfd);
            std::cerr << "listen: " << strerror(errno) << std::endl;
            continue ;
        }

        break ;
    }

    freeaddrinfo(res);

    if (p == NULL)
        return (-1);

    return socketfd;
}

size_t sendall(int fd, const void *buf, size_t size, int flags)
{
    const unsigned char *data = (const unsigned char *)buf;
    size_t sent = 0;
    int n = 0;

    while (sent < size)
    {
        if ((n = send(fd, data + sent, size - sent, flags)) < 0)
            return -1;
        sent += n;
    }
    return sent;
}

int transmit(int from, int to)
{
    char buff[513];
    size_t count, total;

    total = 0;
    while (true)
    {
        memset(buff, 0, 513);
        count = recv(from, buff, 512, 0);
        if (count <= 0)
        {
            std::cerr << "recv: " << strerror(errno) << std::endl;
            return (-1);
        }

        std::cout << buff;

        total += count;

        count = sendall(to, buff, count, 0);
        if (count < 0)
        {
            std::cerr << "send: " << strerror(errno) << std::endl;
            return (-1);
        }

        count = 512;
        while (buff[count] == '\0')
            --count;
        if (buff[count] == '\n' || buff[count] == 'r')
            break ;
    }
    return total;
}

int inspector(int client, int server)
{
    struct pollfd fds[2];
    int events;

    fds[0].events = POLLIN;
    fds[0].fd = client;
    if (fds[0].fd < 0)
        return (-1);

    fds[1].events = POLLIN;
    fds[1].fd = server;
    if (fds[0].fd < 0)
    {
        close(fds[0].fd);
        return (-1);
    }

    while (true)
    {
        events = poll(fds, 2, -1);
        if (events < 0)
            return (-1);

        if (fds[0].revents & POLLIN)
        {
            if (transmit(fds[0].fd, fds[1].fd) < 0)
                return (-1);
        }

        if (fds[1].revents & POLLIN)
        {
            std::cout << "\033[0;31m";
            if (transmit(fds[1].fd, fds[0].fd) < 0)
                return (-1);
            std::cout << "\033[0m";
        }
    }
    return (0);
}

int main(int argc, char **argv)
{
    int proxy, client, server;

    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <server host> <server port> <client port>" << std::endl;
        return (-1);
    }

    proxy = get_socket(NULL, argv[3]);
    std::cout << "ready!" << std::endl;
    client = accept(proxy, NULL, NULL);
    server = get_socket(argv[1], argv[2]);

    return (inspector(client, server));
}
