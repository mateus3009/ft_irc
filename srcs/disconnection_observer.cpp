#include "disconnection_observer.hpp"

disconnection_observer::disconnection_observer(file_descriptor_monitor& monitor) : _monitor(monitor) {}

void disconnection_observer::handle(const int& disconnection)
{
    _monitor.remove(disconnection);
}
