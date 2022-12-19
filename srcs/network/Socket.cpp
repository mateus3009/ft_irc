#include "network/Socket.hpp"

/* Socket */

Socket::Socket(const int& id) : FileDescriptor(id) {}

sockaddr_storage Socket::getsockname(void) const
{
    sockaddr_storage    addr;
    socklen_t           addrlen = sizeof(addr);

    if (::getsockname(_id, (sockaddr*) &addr, &addrlen) < 0)
        throw Error();
    return addr;
}

std::string Socket::getHostname(const sockaddr_storage& addr)
{
    char ipstr[INET6_ADDRSTRLEN];
    if (addr.ss_family == AF_INET)
        inet_ntop(
            addr.ss_family,
            &(((sockaddr_in*) &addr)->sin_addr),
            ipstr,
            INET6_ADDRSTRLEN);
    else
        inet_ntop(
            addr.ss_family,
            &(((sockaddr_in6*) &addr)->sin6_addr),
            ipstr,
            INET6_ADDRSTRLEN);
    return std::string(ipstr);
}

unsigned int Socket::getPort(const sockaddr_storage& addr)
{
    if (addr.ss_family == AF_INET)
        return ntohs(((sockaddr_in*) &addr)->sin_port);
    return ntohs(((sockaddr_in6*) &addr)->sin6_port);
}

/* SocketConnection */

SocketConnection::SocketConnection(const int& id) : FileDescriptor(id) {}

ssize_t SocketConnection::read(void *buf, size_t nbytes) const
{
    const int r = ::recv(_id, buf, nbytes, 0);
    if (r < 0)
        throw Error();
    return r;
}

ssize_t SocketConnection::write(const void *buf, size_t nbytes) const
{
    const int r = ::send(_id, buf, nbytes, 0);
    if (r < 0)
        throw Error();
    return r;
}

sockaddr_storage SocketConnection::getpeername(void) const
{
    sockaddr_storage    addr;
    socklen_t           addrlen = sizeof(addr);

    if (::getpeername(_id, (sockaddr*) &addr, &addrlen) < 0)
        throw Error();
    return addr;
}

std::ostream &operator<<(std::ostream& stream, const SocketConnection& socket)
{
    const sockaddr_storage ss = socket.getpeername();
    return stream
        << "Socket: " << socket.getId()
        << " Hostname: " << socket.getHostname(ss)
        << " Port: " << socket.getPort(ss);
}

/* SocketListener */

SocketListener::SocketListener(const char* port, const char* hostname)
    : Socket()
{
    addrinfo hints;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family     = AF_INET6;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_flags      = AI_PASSIVE;

    addrinfo* res;
    int status = getaddrinfo(hostname, port, &hints, &res);
    if (status < 0)
        throw Error(gai_strerror(status), status);

    int fd;
    addrinfo* p;
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
        throw Error();

    _id = fd;
}

shared_ptr<SocketConnection> SocketListener::accept(void) const
{
    sockaddr_storage addr;
    socklen_t   addrlen = sizeof(addr);
    const int fd = ::accept(_id, (sockaddr*)&addr, &addrlen);
    if (fd < 0)
        throw Error();
    return shared_ptr<SocketConnection>::make_shared(new SocketConnection(fd));
}

std::ostream &operator<<(std::ostream& stream, const SocketListener& socket)
{
    const sockaddr_storage ss = socket.getsockname();
    return stream
        << "Socket: " << socket.getId()
        << " Hostname: " << socket.getHostname(ss)
        << " Port: " << socket.getPort(ss);
}
