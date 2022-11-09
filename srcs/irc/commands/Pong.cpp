#include "irc/commands/Pong.hpp"

const bool Pong::isRegistered = Router::add("PONG", Pong::handle);

void Pong::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&        clientStore,
    ChannelStore&,
    IrcServer&)
{
    if (msg.params.empty())
    {
        client->send(Message() << ERR_NEEDMOREPARAMS << client->getNickname() << "PONG" << "Not enough parameters");
        return ;
    }

    const std::string& token = msg.params.back();

    if (token != "42")
    {
        client->send(Message() << Verb("ERROR") << "Wrong token!");
        client->close();

        clientStore.broadcast(Message() << client->getSource() << Verb("QUIT") << "Quit: Issued a PONG command with invalid token");
    }

}
