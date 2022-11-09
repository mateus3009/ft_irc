#ifndef BUFFER_HPP
# define BUFFER_HPP

# include <list>
# include <vector>
# include <string>
# include <cstring>

# include "Socket.hpp"

# define BUFFER_SIZE 1024

class InputBuffer
{
    private:
        const SocketConnection&     _reader;

        char                        _buffer[BUFFER_SIZE];

        size_t                      _position;

    public:
        InputBuffer(const SocketConnection& reader);

        std::vector<std::string> read(void);

        struct NoSpaceLeftException : std::runtime_error
        {
            NoSpaceLeftException(const char* what);
        };

};

class OutputBuffer
{
    private:
        const SocketConnection&         _writer;

        std::list<std::string>          _messages;

        size_t                          _position;

    public:
        OutputBuffer(const SocketConnection& writer);

        void write(const std::string& str);

        void flush(void);

        size_t queued(void) const;

};

#endif
