#ifndef ERROR_HPP
# define ERROR_HPP

# include <stdexcept>
# include <cerrno>
# include <cstring>

struct Error : std::runtime_error
{
    long code;

    Error(void);

    Error(const char* msg, const long& c = -1);

};

#endif
