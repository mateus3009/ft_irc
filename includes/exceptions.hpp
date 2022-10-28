#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <stdexcept>

struct illegal_access_exception : std::runtime_error
{
    illegal_access_exception(void) : runtime_error("Illegal access exception") {}

    illegal_access_exception(const char* msg) : runtime_error(msg) {}

    illegal_access_exception(const std::string& msg) : runtime_error(msg) {}
};

#endif
