#ifndef FILE_DESCRIPTOR_HPP
# define FILE_DESCRIPTOR_HPP

# include <unistd.h>
# include <stdexcept>
# include <cstring>
# include <cerrno>

# define INVALID_FD -1

class file_descriptor
{
    protected:
        int _fd;

    public:
        file_descriptor(const int& fd = INVALID_FD);

        int get_id() const;

        void close(void);

        bool is_valid(void) const;

};

#endif

