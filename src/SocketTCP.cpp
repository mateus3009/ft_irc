#include "SocketTCP.hpp"

SocketData::SocketData(void) : FileDescriptor(INVALID_FD) {}

SocketData::SocketData(const int& fd) : FileDescriptor(fd) {}

SocketData::SocketData(const SocketData& other) : FileDescriptor(other) {}

SocketData::~SocketData() {}

void SocketData::send(const void* data, size_t size) const
{
    const unsigned char*    buffer;
    size_t                  sent;
    int                     n;

    buffer  = (const unsigned char*)data;
    sent    = 0;

    while (sent < size)
    {
        n = ::send(this->getId(), buffer + sent, size - sent, 0);
        if (n <= 0)
            throw std::runtime_error(strerror(errno));

        sent += n;
    }
}

SocketServer::SocketServer(void) : FileDescriptor(INVALID_FD) {}

SocketServer::SocketServer(const char* port) : FileDescriptor(SocketServer::create(port)) {}

SocketServer::SocketServer(const SocketServer& other) : FileDescriptor(other) {}

SocketServer::~SocketServer() {}

SocketData SocketServer::accept(void) const
{
    int fd;

    fd = ::accept(this->getId(), NULL, NULL);
    if (fd < 0)
        throw std::runtime_error(strerror(errno));

    return SocketData(fd);
}

FileDescriptor SocketServer::create(const char* port)
{
    addrinfo    hints;
    addrinfo    *res;
    addrinfo    *p;
    int         status;
    int         fd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family     = AF_UNSPEC;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_flags      = AI_PASSIVE;

    status = getaddrinfo(NULL, port, &hints, &res);
    if (status < 0)
        throw std::runtime_error(gai_strerror(status));

    status = 1;
    for (p = res; p != NULL; p = p->ai_next)
    {
        fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (fd < 0)
            continue ;

        if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &status, sizeof(status)) < 0
            || bind(fd, p->ai_addr, p->ai_addrlen) < 0
            || listen(fd, 10) < 0)
        {
            ::close(fd);
            continue ;
        }

        break ;
    }

    freeaddrinfo(res);

    if (p == NULL)
        throw std::runtime_error(strerror(errno));

    return FileDescriptor(fd);
}
