#include "output_buffer.hpp"

output_buffer::output_buffer(const socket_connection* connection) : _connection(connection), _messages(), _position(0) {}

void output_buffer::write(const std::string& msg) { _messages.push_back(msg); }

void output_buffer::flush(void)
{
    std::list<std::string>::iterator it = _messages.begin();
    while (it != _messages.end())
    {
        while (_position < it->size())
        {
            const int n = _connection->send(it->c_str() + _position, it->size() - _position);
            if (n <= 0)
                return ;
            _position += n;
        }
        _position = 0;
        _messages.erase(it++);
    }
}

size_t output_buffer::queued(void) const { return _messages.size(); }
