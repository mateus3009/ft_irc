#ifndef FILEDESCRIPTOR_HPP
# define FILEDESCRIPTOR_HPP

# include <unistd.h>
# include <vector>
# include <poll.h>

# include "../utils/observer.hpp"

# define INVALID_FD -1

class FileDescriptor
{
    protected:
        int _id;

    public:
        FileDescriptor(const int& id = INVALID_FD);

        int getId(void) const;

        void close(void);

        bool isValid(void) const;

        struct InvalidFileDescriptorException : public std::runtime_error
        {
            InvalidFileDescriptorException(const char* what);
        };

};

struct Reader
{
    virtual ssize_t receive(void* buf, const size_t& n, const int& flags = 0) const = 0;
};

struct Writer
{
    virtual ssize_t send(const void* buf, const size_t& n, const int& flags = 0) const = 0;
};

#endif
