#include "irc/commands/Motd.hpp"

const bool Motd::isRegistered = Router::add("MOTD", Motd::handle);

void Motd::handle(
    const Message&,
    shared_ptr<Client>  client,
    ClientStore&,
    ChannelStore&,
    IrcServer& ircServer)
{
    if (!client->hasAnyModes(MODE_USER_REGISTERED))
    {
        client->send(Message() << ERR_NOTREGISTERED << "You have not registered");
        return ;
    }

    if (ircServer.getMotd().empty())
    {
        client->send(Message() << ERR_NOMOTD << "MOTD File is missing");
        return ;
    }

    client->send(Message() << RPL_MOTDSTART << std::string("- ").append(ircServer.getServerName()).append(" Message of the day -"));
    client->send(Message() << RPL_MOTD << ircServer.getMotd());
    client->send(Message() << RPL_ENDOFMOTD << "End of /MOTD command.");
}
