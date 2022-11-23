#include "network/FileDescriptor.hpp"

/* FileDescriptor */

FileDescriptor::FileDescriptor(const int& id) : _id(id) {}

int FileDescriptor::getId(void) const { return _id; }

void FileDescriptor::close(void) const
{
    if (::close(_id) < 0)
        throw FileDescriptor::InvalidFileDescriptorException(strerror(errno));
}

FileDescriptor::InvalidFileDescriptorException::InvalidFileDescriptorException(const char* what) : std::runtime_error(what) {}
