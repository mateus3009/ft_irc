#include "irc/commands/Ping.hpp"

const bool Ping::isRegistered = Router::add("PING", Ping::handle);

void Ping::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&,
    ChannelStore&,
    IrcServer&)
{
    if (msg.params.empty())
    {
        client->send(Message() << ERR_NEEDMOREPARAMS << client->getNickname() << "PING" << "Not enough parameters");
        return ;
    }

    client->send(Message() << Verb("PONG") << ":server" << msg.params.front());
}
