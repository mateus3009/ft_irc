#include "irc/commands/Cap.hpp"

const bool Cap::isRegistered = Router::add("CAP", Cap::handle);

void Cap::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&,
    ChannelStore&,
    IrcServer& ircServer)
{
    if (ircServer.isRegistered(client))
    {
        client->send(Message() << ircServer.getSource() << ERR_ALREADYREGISTERED << client->getNickname() << "USER" << "You may not reregister");
        return ;
    }

    if (msg.params.empty())
    {
        client->send(Message() << ircServer.getSource() << ERR_NONICKNAMEGIVEN << client->getNickname() << "*" << "Not enough parameters");
        return ;
    }

    const std::string command = msg.params.front();

    if (command == "LS")
    {
        client->setModes(MODE_USER_CAP_NEGOTIATION);
        client->send(Message() << ircServer.getSource() << Verb("CAP") << client->getNickname() << command << "");
        return ;
    }

    if (command == "END")
    {
        client->unsetModes(MODE_USER_CAP_NEGOTIATION);
        if (ircServer.isRegistered(client))
            client->setModes(MODE_USER_REGISTERED);
    }

    client->send(Message() << ircServer.getSource() << ERR_INVALIDCAPCMD << client->getNickname() << command << "Invalid CAP command");
}
