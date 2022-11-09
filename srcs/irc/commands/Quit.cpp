#include "irc/commands/Quit.hpp"

const bool Quit::isRegistered = Router::add("QUIT", Quit::handle);

void Quit::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&        clientStore,
    ChannelStore&,
    IrcServer&)
{
    client->send(Message() << client->getSource() << Verb("ERROR") << "Bye!");
    client->close();

    std::string reason;
    if (!msg.params.empty())
        reason = *msg.params.begin();

    if (client->hasAnyModes(MODE_USER_REGISTERED))
        clientStore.broadcast(Message() << client->getSource() << Verb("QUIT") << std::string("Quit: ").append(reason));
}