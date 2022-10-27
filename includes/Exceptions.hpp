#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <stdexcept>

struct IllegalAccessException : std::runtime_error
{
    IllegalAccessException(void) : runtime_error("Illegal access exception") {}

    IllegalAccessException(const char* msg) : runtime_error(msg) {}

    IllegalAccessException(const std::string& msg) : runtime_error(msg) {}
};

#endif
