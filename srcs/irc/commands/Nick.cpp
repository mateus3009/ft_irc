#include "irc/commands/Nick.hpp"

const bool Nick::isRegistered = Router::add("NICK", Nick::handle);

void Nick::handle(
    const Message&      msg,
    shared_ptr<Client>& client,
    ClientStore&        clientStore,
    ChannelStore&)
{
    if (msg.params.empty())
    {
        client->send(Message() << ERR_NONICKNAMEGIVEN  << client->getNickname() << "*" << "Not enough parameters");
        return ;
    }

    const std::string nickname = msg.params.front();
    Message::Source src = client->getSource();

    try
    {
        client->setNickname(nickname);
    }
    catch(const Client::AlphaNumericConstraintViolationException&)
    {
        client->send(Message() << ERR_ERRONEUSNICKNAME << nickname << "Erroneus nickname");
    }
    catch(const Client::NicknameIsAlreadyInUseException&)
    {
        client->send(Message() << ERR_NICKNAMEINUSE  << nickname << "Nickname is already in use");
    }

    if (client->hasAnyModes(MODE_USER_REGISTERED))
        clientStore.broadcast(Message() << src << Verb("NICK") << nickname);

    if (!client->getUsername().empty() && client->hasAnyModes(MODE_USER_AUTORIZED))
        client->setModes(MODE_USER_REGISTERED);
}
