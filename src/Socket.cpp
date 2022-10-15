#include "Socket.hpp"

ft::SocketBase::SocketBase(const int& fd) : fd(fd) {}

ft::SocketBase::SocketBase(const SocketBase& other): fd(other.fd) {}

ft::SocketBase::~SocketBase() {}

void ft::SocketBase::close(void) const { ::close(this->fd); }

int ft::SocketBase::getSocket(void) const { return this->fd; }

ft::SocketData::SocketData(const int& fd) : SocketBase(fd) {}

ft::SocketData::SocketData(const SocketData& other) : SocketBase(other) {}

ft::SocketData::~SocketData() {}

void ft::SocketData::send(const void* data, size_t size) const
{
    const unsigned char*    buffer;
    size_t                  sent;
    int                     n;

    buffer  = (const unsigned char*)data;
    sent    = 0;

    while (sent < size)
    {
        n = ::send(this->getSocket(), buffer + sent, size - sent, 0);
        if (n <= 0)
            throw std::runtime_error(strerror(errno));

        sent += n;
    }
}


