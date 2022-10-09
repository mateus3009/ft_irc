#ifndef UTIL_HPP
#define UTIL_HPP

#include <sstream>

template <typename T>
struct AwaysFalse { bool operator()(T) { return false; } };

template <typename T>
std::string ntos(T value)
{
    std::stringstream stream;

    stream << value;
    return stream.str();
};

unsigned int atoui(const char* str)
{
    unsigned int value;
    std::stringstream stream;

    stream << str;
    stream >> value;
    return value;
};

#endif
