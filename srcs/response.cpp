#include "response.hpp"

response::response(connection_handler* connection) : _connection(connection) {}

void response::write(const std::string& msg) { _connection->write(msg); }
