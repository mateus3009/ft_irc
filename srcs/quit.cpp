#include "quit.hpp"

quit::quit() {}

void quit::handle(const request&, response& res)
{
    res.write(":server 000 :bye!");
    res.quit();
}
