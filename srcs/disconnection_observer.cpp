#include "disconnection_observer.hpp"

disconnection_observer::disconnection_observer(file_descriptor_monitor& monitor, client_store& store) : _monitor(monitor), _store(store) {}

void disconnection_observer::handle(const int& id)
{
    _monitor.remove(id);
    _store.remove(id);
}
