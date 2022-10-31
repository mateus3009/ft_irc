#ifndef SOCKET_CONNECTION_HPP
# define SOCKET_CONNECTION_HPP

# include <stdexcept>
# include <cstring>
# include <cerrno>
# include <netdb.h>

# include "file_descriptor.hpp"

class socket_connection : public file_descriptor
{
    public:
        socket_connection();

        socket_connection(const int& fd);

        socket_connection(const socket_connection& other);

        ssize_t send(const void* buf, const size_t& n, const int& flags = 0) const;

        ssize_t receive(void* buf, const size_t& n, const int& flags = 0) const;

};

#endif
