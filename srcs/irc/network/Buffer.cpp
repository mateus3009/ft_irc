#include "irc/network/Buffer.hpp"

/* InputBuffer */

InputBuffer::InputBuffer(const shared_ptr<SocketConnection>& connection)
    : _connection(connection), _buffer(), _position(0)
{
    memset(_buffer, 0, BUFFER_SIZE);
}

std::vector<std::string> InputBuffer::read(void)
{
    if (_position == BUFFER_SIZE)
        throw InputBuffer::NoSpaceLeftException(
            "The buffer has no space left!");

    const int n = _connection->read(
        _buffer + _position, BUFFER_SIZE - _position);
    std::vector<std::string> messages;
    if (n == 0)
        throw ClosedConnectionException("Connection closed by foreign host");

    _position += n;

    if (strchr(_buffer, '\n') == NULL && strchr(_buffer, '\r') == NULL)
        return messages;

    size_t index = 0;
    while (index < _position)
    {
        while (index < _position && (_buffer[index] == '\0'
            || strchr(" \t\r\n", _buffer[index]) != NULL))
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
        messages.push_back(std::string(_buffer + start));
    }

    memmove(_buffer, _buffer + index, _position - index);
    _position -= index;

    return messages;
}

void InputBuffer::clear(void)
{
    memset(_buffer, 0, BUFFER_SIZE);
    _position = 0;
}

InputBuffer::NoSpaceLeftException::NoSpaceLeftException(const char* what)
    : Error(what) {}

InputBuffer::ClosedConnectionException::ClosedConnectionException(const char* what)
    : Error(what) {}

/* OutputBuffer */

OutputBuffer::OutputBuffer(const shared_ptr<SocketConnection>& connection)
    : _connection(connection), _messages(), _position(0) {}

void OutputBuffer::write(const std::string& str)
{
    _messages.push_back(std::string(str).append("\r\n"));
}

void OutputBuffer::flush(void)
{
    std::list<std::string>::iterator it = _messages.begin();
    while (it != _messages.end())
    {
        while (_position < it->size())
        {
            const int n = _connection->write(
                it->c_str() + _position, it->size() - _position);
            if (n <= 0)
                return ;
            _position += n;
        }
        _position = 0;
        _messages.erase(it++);
    }
}

size_t OutputBuffer::queued(void) const { return _messages.size(); }
