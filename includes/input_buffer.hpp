#ifndef INPUT_BUFFER_HPP
# define INPUT_BUFFER_HPP

# include <vector>

# include "socket_connection.hpp"
# include "message.hpp"

# define BUFFER_SIZE 512

class input_buffer
{
    private:
        const socket_connection*    _connection;

        char                        _buffer[BUFFER_SIZE];

        size_t                      _position;

    public:
        input_buffer(const socket_connection* connection);

        std::vector<message> read(void);

};

#endif
