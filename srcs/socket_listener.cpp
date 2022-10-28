#include "socket_listener.hpp"

socket_listener::socket_listener(const char* port) : file_descriptor()
{
    addrinfo    hints;
    addrinfo*   res;
    addrinfo*   p;
    int         status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family     = AF_INET6;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_flags      = AI_PASSIVE;

    status = getaddrinfo(NULL, port, &hints, &res);
    if (status < 0)
        throw std::runtime_error(gai_strerror(status));

    status = 1;
    for (p = res; p != NULL; p = p->ai_next)
    {
        _fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (_fd < 0)
            continue ;

        if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &status, sizeof(status)) < 0
            || bind(_fd, p->ai_addr, p->ai_addrlen) < 0
            || listen(_fd, 10) < 0)
        {
            ::close(_fd);
            continue ;
        }

        break ;
    }

    freeaddrinfo(res);

    if (p == NULL)
        throw std::runtime_error(strerror(errno));
}

socket_connection socket_listener::accept(void) const
{
    int fd;

    fd = ::accept(_fd, NULL, NULL);
    if (fd < 0 )
        throw std::runtime_error(strerror(errno));
    return socket_connection(fd);
}
