#include "utils/Error.hpp"

/* Error */

Error::Error(void) : std::runtime_error(strerror(errno)), code(errno) {}

Error::Error(const char* msg, const long& c)
    : std::runtime_error(msg), code(c) {}
