#include "socket_connection.hpp"

socket_connection::socket_connection(const int& fd) : file_descriptor(fd) {}

socket_connection::socket_connection() : file_descriptor() {}

socket_connection::socket_connection(const socket_connection& other) : file_descriptor(other._fd) {}

ssize_t socket_connection::send(const void* buf, const size_t& n, const int& flags) const
{
    return ::send(_fd, buf, n, flags);
}

ssize_t socket_connection::receive(void* buf, const size_t& n, const int& flags) const
{
    return ::recv(_fd, buf, n, flags);
}
