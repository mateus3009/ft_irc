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

std::string socket_connection::get_hostname(void) const
{
    sockaddr_storage    storage;
    socklen_t           socklen = sizeof(storage);

    getpeername(_fd, (sockaddr*)&storage, &socklen);

    char ipstr[INET6_ADDRSTRLEN];

    void* addr;
    if (((sockaddr*)&storage)->sa_family == AF_INET)
        addr = &(((sockaddr_in*)&storage)->sin_addr);
    else
        addr = &(((sockaddr_in6*)&storage)->sin6_addr);

    inet_ntop(storage.ss_family, addr, ipstr, INET6_ADDRSTRLEN);

    return std::string(ipstr);
}
