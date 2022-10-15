#include "SocketTCP.hpp"

SocketData::SocketData(void) : FileDescriptor(INVALID_FD) {}

SocketData::SocketData(const FileDescriptor& fd) : FileDescriptor(fd) {}

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

SocketServer::SocketServer(const FileDescriptor& fd) : FileDescriptor(fd) {}

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

