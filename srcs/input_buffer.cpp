#include "input_buffer.hpp"

input_buffer::input_buffer(const socket_connection* connection) : _connection(connection), _buffer(), _position(0)
{
    memset(_buffer, 0, BUFFER_SIZE);
}

std::vector<message> input_buffer::read(void)
{
    const int n = _connection->receive(_buffer + _position, BUFFER_SIZE - _position);
    std::vector<message> messages;
    if (n <= 0)
        return messages;

    _position += n;

    if (strchr(_buffer, '\n') == NULL && strchr(_buffer, '\r') == NULL)
        return messages;

    size_t index = 0;
    while (index < _position)
    {
        while (index < _position && (_buffer[index] == '\0' || strchr(" \t\r\n", _buffer[index]) != NULL))
            ++index;
        if (index == _position)
            break ;

        int start = index;

        while (index < _position && strchr("\r\n", _buffer[index]) == NULL)
        {
            if (_buffer[index] == '\0')
                _buffer[index] = '\?';
            ++index;
        }
        if (index == _position)
            break ;

        _buffer[index] = '\0';
        messages.push_back(message::parse(_buffer + start));
    }

    memmove(_buffer, _buffer + index, _position - index);
    _position -= index;

    return messages;
}

bool input_buffer::full(void) const { return _position == BUFFER_SIZE; }
