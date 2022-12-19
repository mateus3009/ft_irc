#ifndef BUFFER_HPP
# define BUFFER_HPP

# include <list>
# include <vector>
# include <string>
# include <cstring>
# include <algorithm>

# include "../../network/Socket.hpp"

# define BUFFER_SIZE 1024

class InputBuffer
{
    private:
        shared_ptr<SocketConnection>    _connection;

        char                            _buffer[BUFFER_SIZE];

        size_t                          _position;

    public:
        InputBuffer(shared_ptr<SocketConnection> connection);

        std::vector<std::string> read(void);

        void clear(void);

        struct NoSpaceLeftException : Error
        {
            NoSpaceLeftException(const char* what);
        };

        struct ClosedConnectionException : Error
        {
            ClosedConnectionException(const char* what);
        };

};

class OutputBuffer
{
    private:
        shared_ptr<SocketConnection>    _connection;

        std::list<std::string>          _messages;

        size_t                          _position;

    public:
        OutputBuffer(shared_ptr<SocketConnection> connection);

        void write(const std::string& str);

        void flush(void);

        size_t queued(void) const;

};

#endif
