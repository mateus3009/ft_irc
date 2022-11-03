#include "pass.hpp"

pass::pass(client_store& store, const std::string& password) : _store(store), _password(password) {}

void pass::handle(const request& req, response& res)
{
    client* c = _store.find(req.id);
    if (c->is_authorized())
    {
        res.write(":server 462 <client> :You are already registered!");
        return ;
    }

    if (req.message.params.empty())
    {
        res.write(":server 461 <client> :Need more params!");
        return ;
    }

    if (*req.message.params.begin() != _password)
    {
        res.write(":server 464 <client> :Need more params!");
        return ;
    }

    c->authorize();
}
