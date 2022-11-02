#include "connection_observer.hpp"

connection_observer::connection_observer(file_descriptor_monitor& monitor) : _monitor(monitor) {}

void connection_observer::handle(std::pair<const connection, response>& connection)
{
    std::cout << "new connection from: " << connection.first.hostname << std::endl;
    _monitor.add(connection.first.id);
}
