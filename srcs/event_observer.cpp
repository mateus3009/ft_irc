#include "event_observer.hpp"

event_observer::event_observer(socket_server& store) : _store(store) {}

void event_observer::handle(pollfd& event) { _store.handle(event); }
