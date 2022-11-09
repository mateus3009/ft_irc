#include "network/FileDescriptor.hpp"

/* FileDescriptor */

FileDescriptor::FileDescriptor(const int& id) : _id(id) {}

int FileDescriptor::getId(void) const { return _id; }

void FileDescriptor::close(void)
{
    if (::close(_id) < 0)
        throw FileDescriptor::InvalidFileDescriptorException("Closing invalid file descriptor!");
    _id = INVALID_FD;
}

bool FileDescriptor::isValid(void) const { return _id != INVALID_FD; }

FileDescriptor::InvalidFileDescriptorException::InvalidFileDescriptorException(const char* what) : std::runtime_error(what) {}
