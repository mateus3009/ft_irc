#ifndef FILEDESCRIPTOR_HPP
# define FILEDESCRIPTOR_HPP

# include <unistd.h>
# include <iostream>
# include <string>

# include "../utils/Error.hpp"

# define INVALID_FD -1

class FileDescriptor
{
    protected:
        int _id;

    public:
        FileDescriptor(const int& id = INVALID_FD);

        virtual ~FileDescriptor();

        int getId(void) const;

        virtual void close(void) const;

};

class FileDescriptorInteractive : public virtual FileDescriptor
{
    public:
        FileDescriptorInteractive(const int& id = INVALID_FD);

        virtual ssize_t read(void *buf, size_t nbytes) const;

        virtual ssize_t write(const void *buf, size_t nbytes) const;
};

std::ostream &operator<<(std::ostream& stream, const FileDescriptor& fd);

#endif
