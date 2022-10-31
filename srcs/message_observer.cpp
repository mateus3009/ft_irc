#include "message_observer.hpp"

void message_observer::handle(std::pair<request, response>& rr)
{
    std::cout << rr.first.id << ": " << rr.first.message.to_string() << std::endl;
}
