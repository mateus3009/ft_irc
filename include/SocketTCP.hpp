#ifndef SOCKETTCP_HPP
# define SOCKETTCP_HPP

# include "FileDescriptor.hpp"

# include <netdb.h>

class SocketData : public virtual FileDescriptor
{
    public:
        SocketData(void);

        SocketData(const int& fd);

        SocketData(const SocketData& other);

        virtual ~SocketData();

        void send(const void* data, size_t size) const;

        template <typename F>
        void receive(void* data, size_t size, F has_end) const;
};

template <typename F>
void SocketData::receive(void* data, size_t size, F has_end) const
{
    unsigned char*  buffer;
    size_t          received;
    int             n;

    buffer      = (unsigned char*)data;
    received    = 0;

    while (receive < size)
    {
        n = recv(this->getSocket(), buffer + received, size - received, 0);
        if (n <= 0)
            throw std::runtime_error(strerror(errno));

        received += n;

        if (has_end(data))
            break ;
    }
};

class SocketServer : public virtual FileDescriptor
{
    private:
        static FileDescriptor SocketServer::create(const char* port);

    public:
        SocketServer(void);

        SocketServer(const char* port);

        SocketServer(const SocketServer& other);

        virtual ~SocketServer();

        SocketData accept(void) const;
};

#endif
