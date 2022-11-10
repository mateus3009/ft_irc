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
        client->send(Message() << ircServer.getSource() << ERR_NOTREGISTERED << "You have not registered");
        return ;
    }

    showMotd(client, ircServer);
}


void Motd::showMotd(
    shared_ptr<Client>  client,
    IrcServer&          ircServer)
{
    if (ircServer.getMotd().empty())
    {
        client->send(Message() << ircServer.getSource() << ERR_NOMOTD << "MOTD File is missing");
        return ;
    }

    client->send(Message() << ircServer.getSource() << RPL_MOTDSTART << std::string("- ").append(ircServer.getServerName()).append(" Message of the day -"));
    client->send(Message() << ircServer.getSource() << RPL_MOTD << ircServer.getMotd());
    client->send(Message() << ircServer.getSource() << RPL_ENDOFMOTD << "End of /MOTD command.");
}

