#include "router.hpp"

bool router::add(std::string verb, route* r)
{
    return _routes.insert(std::make_pair(verb, r)).second;
}

void router::call(const request& req, response& res)
{
    std::map<std::string, route*>::iterator it = _routes.find(req.message.verb);
    if (it == _routes.end())
        res.write("Command not found! Try /HELP");
    else
        it->second->handle(req, res);
}
