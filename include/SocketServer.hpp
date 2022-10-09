#ifndef SOCKETSERVER_HPP
#define SOCKETSERVER_HPP

#include <unistd.h>
#include <algorithm>
#include <netdb.h>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <map>
#include <poll.h>
#include <cerrno>

#include "Util.hpp"

class SocketBase
{
    private:
        int fd;

    public:
        SocketBase(void);

        SocketBase(const int& fd);

        SocketBase(const SocketBase& other);

        virtual ~SocketBase();

        SocketBase& operator=(const SocketBase& other);

        void swap(SocketBase& base);

        void close(void);

        int getSocket(void) const;

};

class SocketData : public SocketBase
{
    public:
        SocketData(void);

        SocketData(const int& fd);

        SocketData(const SocketData& other);

        virtual ~SocketData();

        void send(void* data, size_t size) const;

        size_t get(void* data, size_t size) const;

        template <typename F>
        size_t get(void* data, size_t size, F finder) const
        {
            unsigned char*  buffer;
            size_t          received;
            int             n;

            buffer = (unsigned char*)data;
            received = 0;
            while (received < size)
            {
                n = recv(this->getSocket(), buffer + received, size - received, 0);
                if (n < 0)
                    throw std::runtime_error(strerror(errno));
                received += n;
                if (finder(data))
                    break ;
            }
            return received;
        }
};

class SocketServer : public SocketBase
{
    protected:
        static int create(const unsigned int& port);

    public:
        SocketServer(void);

        SocketServer(const unsigned int& port);

        SocketServer(SocketServer& other);

        virtual ~SocketServer();

        SocketData accept(void) const;

};

class SocketInputHandler : public SocketBase
{
    public:
        virtual void handle(void) = 0;
};

class SocketListener
{
    private:
        std::vector<pollfd> fds;
        std::map<int, SocketInputHandler*> handlers;

    public:
        SocketListener(void);

        SocketListener(const SocketListener& other);

        virtual ~SocketListener();

        void add(SocketInputHandler* handler);

        void remove(const int& fd);

        void listen(void);

};

#endif
