#include "irc/commands/User.hpp"

const bool User::isRegistered = Router::add("USER", User::handle);

void User::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&,
    ChannelStore&,
    IrcServer&)
{
    if (msg.params.size() < 4)
    {
        client->send(Message() << ERR_NEEDMOREPARAMS << client->getNickname() << "USER" << "Not enough parameters");
        return ;
    }

    if (!client->getUsername().empty())
    {
        client->send(Message() << ERR_ALREADYREGISTERED << client->getNickname() << "USER" << "You may not reregister");
        return ;
    }

    const std::string& username = msg.params[0];
    client->setUsername(username);

    const std::string& realName = msg.params[3];
    client->setRealName(realName);

    if (!client->getNickname().empty() && client->hasAnyModes(MODE_USER_AUTORIZED))
        client->setModes(MODE_USER_REGISTERED);

}
