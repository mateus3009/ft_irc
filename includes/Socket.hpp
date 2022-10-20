#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <unistd.h>
# include <stdexcept>
# include <cstring>
# include <cerrno>
# include <netdb.h>

# define INVALID_FD -1

class FileDescriptor
{
    protected:
        int _fd;

    public:
        explicit FileDescriptor(const int& fd = INVALID_FD);

        FileDescriptor(const FileDescriptor& other);

        virtual ~FileDescriptor();

        FileDescriptor operator=(const FileDescriptor& other);

        int getId() const;

        void close(void);

};

class SocketConnection : public FileDescriptor
{
    public:
        SocketConnection(void);

        explicit SocketConnection(const int& fd);

        SocketConnection(const SocketConnection& other);

        virtual ~SocketConnection();

        SocketConnection& operator=(const SocketConnection& other);

        ssize_t send(const void* buf, const size_t& n, const int& flags = 0) const;

        ssize_t receive(void* buf, const size_t& n, const int& flags = 0) const;

};

class SocketListener : public FileDescriptor
{
    public:
        SocketListener(void);

        explicit SocketListener(const int& fd);

        explicit SocketListener(const char* port);

        SocketListener(const SocketListener& other);

        virtual ~SocketListener();

        SocketListener& operator=(const SocketListener& other);

        SocketConnection accept(void) const;

};

#endif
