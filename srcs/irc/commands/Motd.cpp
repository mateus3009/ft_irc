#include "irc/commands/Motd.hpp"

const bool Motd::isRegistered = Router::add("MOTD", Motd::handle);

void Motd::handle(
    const Message&,
    shared_ptr<Client>& client,
    ClientStore&,
    ChannelStore&)
{
    if (!client->hasAnyModes(MODE_USER_REGISTERED))
    {
        client->send(Message() << ERR_NOTREGISTERED << "You have not registered");
        return ;
    }

    client->send(Message() << ERR_NOMOTD << "MOTD File is missing");
}
