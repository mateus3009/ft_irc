#include "network/FileDescriptor.hpp"

FileDescriptor::FileDescriptor(const int& id) : _id(id) {}

FileDescriptor::~FileDescriptor()
{
    if (_id != INVALID_FD)
        close();
}

int FileDescriptor::getId(void) const { return _id; }

void FileDescriptor::close(void) const
{
    if (::close(_id) < 0)
        throw Error();
}

FileDescriptorInteractive::FileDescriptorInteractive(const int& id)
    : FileDescriptor(id) {}

ssize_t FileDescriptorInteractive::read(void *buf, size_t nbytes) const
{
    const int r = ::read(_id, buf, nbytes);
    if (r < 0)
        throw Error();
    return r;
}

ssize_t FileDescriptorInteractive::write(const void *buf, size_t nbytes) const
{
    const int r = ::write(_id, buf, nbytes);
    if (r < 0)
        throw Error();
    return r;
}

std::ostream &operator<<(std::ostream& stream, const FileDescriptor& fd)
{
    return stream << "File descriptor: " << fd.getId();
}
