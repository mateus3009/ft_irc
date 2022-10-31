#include "help.hpp"

bool help::is_registered = router::add("HELP", help::route);

void help::route(request& req, response& res)
{
    if (req.message.params.empty())
    {
        res.write(":server 704 val * :** Help System **");
        res.write(":server 705 val * :");
        res.write(":server 705 val * :Try /HELP <command> for specific help");
        return ;
    }

    res.write(":server 704 val * :Unknown command!");
}
