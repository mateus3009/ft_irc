#include "response.hpp"

response::response(shared_ptr<connection_handler> connection) : _connection(connection) {}

void response::write(const std::string& msg) { _connection->write(msg); }
