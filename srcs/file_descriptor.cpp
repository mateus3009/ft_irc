#include "file_descriptor.hpp"

file_descriptor::file_descriptor(const int& fd) : _fd(fd) {}

int file_descriptor::get_id() const { return _fd; }

void file_descriptor::close(void)
{
    if (::close(_fd) < 0)
        throw std::runtime_error(strerror(errno));
    _fd = INVALID_FD;
}
