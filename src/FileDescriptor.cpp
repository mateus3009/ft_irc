#include "FileDescriptor.hpp"

FileDescriptor::FileDescriptor(void) : id(INVALID_FD) {}

FileDescriptor::FileDescriptor(const int& fd) : id(fd) {}

FileDescriptor::FileDescriptor(const FileDescriptor& other) : id(other.id) {}

FileDescriptor::~FileDescriptor() {}

FileDescriptor& FileDescriptor::operator=(const FileDescriptor& other)
{
    this->id = other.id;
    return *this;
}

int FileDescriptor::getId(void) const { return this->id; }

void FileDescriptor::close(void) const
{
    if (::close(this->id) < 0)
        throw std::runtime_error(strerror(errno));
}
