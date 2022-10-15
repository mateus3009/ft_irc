#ifndef SOCKETSERVER_HPP
#define SOCKETSERVER_HPP

#include <cstddef>
#include <unistd.h>
#include <netdb.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>

namespace ft
{
    class SocketBase
    {
        private:
            int fd;

        public:
            SocketBase(const int& fd);

            SocketBase(const SocketBase& other);

            virtual ~SocketBase();

            void close(void) const;

            int getSocket(void) const;
    };

    class SocketData : public virtual SocketBase
    {
        public:
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
    }

};

#endif
