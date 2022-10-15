#include "FileDescriptor.hpp"

FileDescriptor::FileDescriptor(void) : _id(INVALID_FD) {}

FileDescriptor::FileDescriptor(const int& fd) : _id(fd) {}

FileDescriptor::FileDescriptor(const FileDescriptor& other) : _id(other._id) {}

FileDescriptor::~FileDescriptor() {}

FileDescriptor& FileDescriptor::operator=(const FileDescriptor& other)
{
    this->_id = other._id;
    return *this;
}

int FileDescriptor::getId(void) const { return this->_id; }

void FileDescriptor::close(void) const
{
    if (::close(this->_id) < 0)
        throw std::runtime_error(strerror(errno));
}
