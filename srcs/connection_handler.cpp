#include "connection_handler.hpp"

connection_handler::connection_handler(const socket_connection& connection) : _connection(connection), _input(&connection), _output(&connection), closing(false) {}

int connection_handler::get_id(void) const { return _connection.get_id(); }

std::vector<message> connection_handler::read(void) { return _input.read(); }

void connection_handler::write(const std::string& str)
{
    std::stringstream stream;

    stream << str << "\r\n";
    _output.write(stream.str());
}

void connection_handler::flush(void) { _output.flush(); }

response connection_handler::get_response(void) { return response(this); }

std::string connection_handler::get_hostname(void) const { return _connection.get_hostname(); }

void connection_handler::close(void)
{
    if (!_connection.is_valid())
        return ;
    _connection.close();
}

size_t connection_handler::queued(void) const { return _output.queued(); }

bool operator==(const connection_handler& l, const int& r) { return l.get_id() == r; }
