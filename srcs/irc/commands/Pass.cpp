#include "irc/commands/Pass.hpp"

const bool Pass::isRegistered = Router::add("PASS", Pass::handle);

void Pass::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&,
    ChannelStore&,
    IrcServer& ircServer)
{
    if (client->hasAnyModes(MODE_USER_AUTORIZED))
    {
        client->send(Message() << ircServer.getSource() << ERR_ALREADYREGISTERED << client->getNickname() << "PASS" << "You may not reregister");
        return ;
    }

    if (msg.params.empty())
    {
        client->send(Message() << ircServer.getSource() << ERR_NEEDMOREPARAMS << client->getNickname() << "PASS" << "Not enough parameters");
        return ;
    }

    if (msg.params.front() != ircServer.getPassword())
    {
        client->send(Message() << ircServer.getSource() << ERR_PASSWDMISMATCH << client->getNickname() << "Password incorrect");
        client->send(Message() << ircServer.getSource() << Verb("ERROR") << "Password incorrect");
        client->close();
        return ;
    }

    client->setModes(MODE_USER_AUTORIZED);

    if (!client->getNickname().empty() && !client->getUsername().empty())
    {
        client->setModes(MODE_USER_REGISTERED);
        Motd::showMotd(client, ircServer);
    }
}
