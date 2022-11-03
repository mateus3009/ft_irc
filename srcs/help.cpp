#include "help.hpp"

help::help(client_store& store) : _store(store) {}

void help::handle(const request& req, response& res)
{
    client* c = _store.find(req.id);

    std::cout << "nickname: " << c->get_nickname() << std::endl;

    if (req.message.params.empty())
    {
        res.write(":server 704 val * :** Help System **");
        res.write(":server 705 val * :");
        res.write(":server 705 val * :Try /HELP <command> for specific help");
        return ;
    }

    res.write(":server 704 val * :Unknown command!");
}
