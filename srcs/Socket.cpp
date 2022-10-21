#include "Socket.hpp"

FileDescriptor::FileDescriptor(const int& fd) : _fd(fd) {}

FileDescriptor::FileDescriptor(const FileDescriptor& other) : _fd(other._fd) {}

FileDescriptor::~FileDescriptor() {}

FileDescriptor FileDescriptor::operator=(const FileDescriptor& other)
{
    _fd = other._fd;
    return *this;
}

int FileDescriptor::getId() const { return _fd; }

void FileDescriptor::close(void)
{
    if (::close(_fd) < 0)
        throw std::runtime_error(strerror(errno));
    _fd = INVALID_FD;
}

SocketConnection::SocketConnection(void) : FileDescriptor() {}

SocketConnection::SocketConnection(const int& fd) : FileDescriptor(fd) {}

SocketConnection::SocketConnection(const SocketConnection& other) : FileDescriptor(other) {}

SocketConnection::~SocketConnection() {}

SocketConnection& SocketConnection::operator=(const SocketConnection& other)
{
    FileDescriptor::operator=(other);
    return *this;
}

ssize_t SocketConnection::send(const void* buf, const size_t& n, const int& flags) const
{
    ssize_t sent;

    sent = ::send(_fd, buf, n, flags);
    if (sent < 0)
        throw std::runtime_error(strerror(errno));
    return sent;
}

ssize_t SocketConnection::receive(void* buf, const size_t& n, const int& flags) const
{
    ssize_t received;

    received = ::recv(_fd, buf, n, flags);
    if (received < 0)
        throw std::runtime_error(strerror(errno));
    return received;
}

SocketListener::SocketListener(void) : FileDescriptor() {}

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

SocketListener::SocketListener(const SocketListener& other) : FileDescriptor(other) {}

SocketListener::~SocketListener() {}

SocketListener& SocketListener::operator=(const SocketListener& other)
{
    FileDescriptor::operator=(other);
    return *this;
}

SocketConnection SocketListener::accept(void) const
{
    int fd;

    fd = ::accept(_fd, NULL, NULL);
    if (fd < 0 )
        throw std::runtime_error(strerror(errno));
    return SocketConnection(fd);
}
