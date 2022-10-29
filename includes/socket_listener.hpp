#ifndef SOCKET_LISTENER_HPP
# define SOCKET_LISTENER_HPP

# include "file_descriptor.hpp"
# include "socket_connection.hpp"

class socket_listener : public file_descriptor
{
    public:
        explicit socket_listener(const char* port);

        socket_connection accept(void) const;

};

#endif
