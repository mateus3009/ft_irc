#ifndef FILEDESCRIPTOR_HPP
# define FILEDESCRIPTOR_HPP

# include <unistd.h>
# include <cstring>
# include <cerrno>
# include <stdexcept>

# define INVALID_FD -1

class FileDescriptor
{
    private:
        int _id;

    public:
        FileDescriptor(void);

        FileDescriptor(const int& fd);

        FileDescriptor(const FileDescriptor& other);

        virtual ~FileDescriptor();

        FileDescriptor& operator=(const FileDescriptor& other);

        int getId(void) const;

        void close(void) const;
};

#endif
