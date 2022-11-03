#include "connection_observer.hpp"

connection_observer::connection_observer(file_descriptor_monitor& monitor, client_store& store) : _monitor(monitor), _store(store) {}

void connection_observer::handle(std::pair<const connection, response>& event)
{
    _monitor.add(event.first.id);
    _store.add(event.first.id, event.first.hostname);
}
