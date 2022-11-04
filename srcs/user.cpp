#include "user.hpp"

user::user(client_store& store) : _store(store) {}

void user::handle(const request& req, response& res)
{
    client* c = _store.find(req.id);
    if (!c->get_username().empty())
    {
        res.write(":server 462 <client> :You are already registered!");
        return ;
    }

    if (req.message.params.size() < 4)
    {
        res.write(":server 461 <client> :Need more params!");
        return ;
    }

    c->set_username(*req.message.params.begin());
}
