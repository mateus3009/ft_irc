#include "connection_observer.hpp"

connection_observer::connection_observer(file_descriptor_monitor& monitor) : _monitor(monitor) {}

void connection_observer::handle(std::pair<const int, response>& connection) { _monitor.add(connection.first); }
