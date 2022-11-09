#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <netdb.h>
# include <arpa/inet.h>
# include <string>
# include <cerrno>
# include <stdexcept>
# include <cstring>

# include "FileDescriptor.hpp"

class SocketConnection : public FileDescriptor, public Reader, public Writer
{
    public:
        SocketConnection();

        SocketConnection(const int& fd);

        SocketConnection(const SocketConnection& other);

        ssize_t send(const void* buf, const size_t& n, const int& flags = 0) const;

        ssize_t receive(void* buf, const size_t& n, const int& flags = 0) const;

        std::string get_hostname(void) const;

};

class SocketListener : public FileDescriptor
{
    public:
        SocketListener(const char* port);

        SocketConnection accept(void) const;

};

#endif

