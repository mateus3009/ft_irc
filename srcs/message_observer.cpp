#include "message_observer.hpp"

message_observer::message_observer(router* router) : _router(router) {}

void message_observer::handle(std::pair<const request, response>& rr)
{
    _router->call(rr.first, rr.second);
}
