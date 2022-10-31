#include "router.hpp"

std::map<std::string, router::route_handler> router::_routes;

bool router::add(std::string verb, router::route_handler r)
{
    return _routes.insert(std::make_pair(verb, r)).second;
}

void router::route(request& req, response& res)
{
    std::map<std::string, router::route_handler>::iterator it = _routes.find(req.message.verb);
    if (it == _routes.end())
        res.write("Command not found!");
    else
        it->second(req, res);
}
