#include "network/Socket.hpp"

/* SocketConnection */

SocketConnection::SocketConnection(const int& id) : FileDescriptor(id) {}

SocketConnection::SocketConnection() : FileDescriptor() {}

SocketConnection::SocketConnection(const SocketConnection& other) : FileDescriptor(other._id) {}

ssize_t SocketConnection::send(const void* buf, const size_t& n, const int& flags) const
{
    int sent = ::send(_id, buf, n, flags);
    if (sent == 0 && n != 0)
        shutdown(_id, SHUT_RDWR);
    return sent;
}

ssize_t SocketConnection::receive(void* buf, const size_t& n, const int& flags) const
{
    int received = ::recv(_id, buf, n, flags);
    if (received == 0)
        shutdown(_id, SHUT_RDWR);
    return received;
}

std::string SocketConnection::get_hostname(void) const
{
    sockaddr_storage    storage;
    socklen_t           socklen = sizeof(storage);

    getpeername(_id, (sockaddr*)&storage, &socklen);

    char ipstr[INET6_ADDRSTRLEN];

    void* addr;
    if (((sockaddr*)&storage)->sa_family == AF_INET)
        addr = &(((sockaddr_in*)&storage)->sin_addr);
    else
        addr = &(((sockaddr_in6*)&storage)->sin6_addr);

    inet_ntop(storage.ss_family, addr, ipstr, INET6_ADDRSTRLEN);

    return std::string(ipstr);
}

/* SocketListener */

SocketListener::SocketListener(const char* port) : FileDescriptor()
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
        _id = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (_id < 0)
            continue ;

        if (setsockopt(_id, SOL_SOCKET, SO_REUSEADDR, &status, sizeof(status)) < 0
            || bind(_id, p->ai_addr, p->ai_addrlen) < 0
            || listen(_id, 10) < 0)
        {
            ::close(_id);
            continue ;
        }

        break ;
    }

    freeaddrinfo(res);

    if (p == NULL)
        throw std::runtime_error(strerror(errno));
}

SocketConnection SocketListener::accept(void) const
{
    int fd;

    fd = ::accept(_id, NULL, NULL);
    if (fd < 0 )
        throw std::runtime_error(strerror(errno));
    return SocketConnection(fd);
}

