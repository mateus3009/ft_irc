#ifndef OUTPUT_BUFFER
# define OUTPUT_BUFFER

# include <list>
# include <string>

# include "socket_connection.hpp"
# include "message.hpp"

class output_buffer
{
    private:
        const socket_connection*    _connection;

        std::list<std::string>      _messages;

        size_t                      _position;

    public:
        output_buffer(const socket_connection* connection);

        void write(const std::string& msg);

        void flush(void);

        size_t  queued(void) const;

};

#endif
