#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <netdb.h>
# include <arpa/inet.h>

# include "../utils/Error.hpp"
# include "../utils/shared_ptr.hpp"
# include "FileDescriptor.hpp"

class Socket : public virtual FileDescriptor
{
    public:
        Socket(const int& id = INVALID_FD);

        sockaddr_storage getsockname(void) const;

        static std::string getHostname(const sockaddr_storage& addr);

        static unsigned int getPort(const sockaddr_storage& addr);
};

class SocketConnection :
    public virtual FileDescriptor,
    public virtual FileDescriptorInteractive,
    public virtual Socket
{
    public:
        SocketConnection(const int& id = INVALID_FD);

        virtual ssize_t read(void *buf, size_t nbytes) const;

        virtual ssize_t write(const void *buf, size_t nbytes) const;

        sockaddr_storage getpeername(void) const;
};

std::ostream &operator<<(std::ostream& stream, const SocketConnection& socket);

class SocketListener : public virtual Socket
{
    public:
        SocketListener(const char* port = "0", const char* hostname = NULL);

        virtual shared_ptr<SocketConnection> accept(void) const;
};

std::ostream &operator<<(std::ostream& stream, const SocketListener& socket);

#endif
