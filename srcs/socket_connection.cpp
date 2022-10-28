#include "socket_connection.hpp"

socket_connection::socket_connection(const int& fd) : file_descriptor(fd) {}

ssize_t socket_connection::send(const void* buf, const size_t& n, const int& flags) const
{
    ssize_t sent;

    sent = ::send(_fd, buf, n, flags);
    if (sent < 0)
        throw std::runtime_error(strerror(errno));
    return sent;
}

ssize_t socket_connection::receive(void* buf, const size_t& n, const int& flags) const
{
    ssize_t received;

    received = ::recv(_fd, buf, n, flags);
    if (received < 0)
        throw std::runtime_error(strerror(errno));
    return received;
}
