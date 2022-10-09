#include "SocketServer.hpp"

SocketBase::SocketBase(void) : fd() {}

SocketBase::SocketBase(const int& fd) : fd(fd) {}

SocketBase::SocketBase(const SocketBase& other) : fd(other.fd) {}

SocketBase::~SocketBase() {}

SocketBase& SocketBase::operator=(const SocketBase& other)
{
    this->fd = other.fd;
    return *this;
}

void SocketBase::swap(SocketBase& other)
{ std::swap(this->fd, other.fd); }

void SocketBase::close(void)
{ ::close(this->fd); }

int SocketBase::getSocket(void) const
{ return this->fd; }

SocketData::SocketData(void) : SocketBase() {}

SocketData::SocketData(const int& fd) : SocketBase(fd) {};

SocketData::SocketData(const SocketData& other) : SocketBase(other) {};

SocketData::~SocketData() {}

SocketData& SocketData::operator=(const SocketData& other)
{
    SocketBase::operator=(other);
    return *this;
}

void SocketData::send(void* data, size_t size) const
{
    unsigned char*  buffer;
    size_t          sent;
    int             n;

    buffer = (unsigned char*)data;
    sent = 0;
    while (sent < size)
    {
        n = ::send(this->getSocket(), buffer + sent, size - sent, 0);
        if (n < 0)
            throw std::runtime_error(strerror(errno));
        sent += n;
    }
}

size_t SocketData::get(void* data, size_t size) const
{ return get(data, size, AwaysFalse<void*>()); }

int SocketServer::create(const unsigned int& port)
{
    addrinfo    hints;
    addrinfo*   res;
    addrinfo*   p;
    int         status;
    int         fd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family     = AF_UNSPEC;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_flags      = AI_PASSIVE;

    status = getaddrinfo(NULL, ntos(port).c_str(), &hints, &res);
    if (status < 0)
        throw std::runtime_error(gai_strerror(status));

    status = 1;
    for (p = res; p != NULL; p = p->ai_next)
    {
        fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (fd < 0)
            continue ;

        if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &status, sizeof(int)) < 0
            || bind(fd, p->ai_addr, p->ai_addrlen) < 0
            || listen(fd, 100) < 0)
        {
            ::close(fd);
            continue ;
        }

        break ;
    }

    freeaddrinfo(res);

    if (p == NULL)
        throw std::runtime_error(strerror(errno));

    return (fd);
}

SocketServer::SocketServer(void) : SocketBase() {}

SocketServer::SocketServer(const unsigned int& port)
    : SocketBase(SocketServer::create(port)) {}

SocketServer::SocketServer(SocketServer& other) : SocketBase(other) {}

SocketServer::~SocketServer() {}

SocketServer& SocketServer::operator=(const SocketServer& other)
{
    SocketBase::operator=(other);
    return *this;
}

SocketData SocketServer::accept(void) const
{
    int newfd;
    SocketData d(2);

    newfd = ::accept(this->getSocket(), NULL, NULL);
    if (newfd < 0)
        throw std::runtime_error(strerror(errno));
    return SocketData(newfd);
}

SocketListener::SocketListener(void) : fds(), handlers() {}

SocketListener::SocketListener(const SocketListener& other)
    : fds(other.fds), handlers(other.handlers) {}

SocketListener::~SocketListener() {}

SocketListener& SocketListener::operator=(const SocketListener& other)
{
    this->fds       = other.fds;
    this->handlers  = other.handlers;
    return *this;
}

void SocketListener::add(SocketInputHandler* handler)
{
    int fd;

    fd = handler->getSocket();
    if (handlers.insert(std::make_pair(3, handler)).second)
        fds.push_back((pollfd){ .fd = fd, .events = POLLIN });
}

void SocketListener::remove(const int& fd)
{
    handlers.erase(handlers.find(fd));
    for (std::vector<pollfd>::iterator it = fds.end(); it != fds.end(); ++it)
    {
        if (it->fd == fd)
        {
            fds.erase(it);
            break ;
        }
    }
}

void SocketListener::listen(void)
{
    int events;

    if (fds.empty())
        throw std::runtime_error("Nothing to listen to");

    while (true)
    {
        events = poll(fds.data(), fds.size(), 10000);
        if (events < 0)
            throw std::runtime_error(strerror(errno));
        for (std::vector<pollfd>::iterator it = fds.end(); it != fds.end(); ++it)
        {
            if (it->revents & POLLIN)
                handlers.find(it->fd)->second->handle();
        }
    }
}
