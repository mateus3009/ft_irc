#include "irc/commands/Nick.hpp"

const bool Nick::isRegistered = Router::add("NICK", Nick::handle);

void Nick::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&        clientStore,
    ChannelStore&,
    IrcServer& ircServer)
{
	std::cout << "NICK sendo chamado com cliente: " << client->getIdClient() << " with command: " << ((msg.params.empty()) ? "nothing" : msg.params.front()) << std::endl;

    if (msg.params.empty())
    {
        client->send(Message() << ircServer.getSource() << ERR_NONICKNAMEGIVEN  << client->getNickname() << "*" << "Not enough parameters");
        return ;
    }

    const std::string nickname = msg.params.front();
    Message::Source src = client->getSource();

    try
    {
        client->setNickname(nickname);
    }
    catch(const Client::AlphaNumericConstraintViolationException& e)
    {
        client->send(Message() << ircServer.getSource() << ERR_ERRONEUSNICKNAME << nickname << "Erroneus nickname");
    }
    catch(const Client::NicknameIsAlreadyInUseException& e)
    {
        client->send(Message() << ircServer.getSource() << ERR_NICKNAMEINUSE  << nickname << "Nickname is already in use");
    }

    if (ircServer.isRegistered(client))
        clientStore.broadcast(Message() << src << Verb("NICK") << nickname);

    if (ircServer.isRegistered(client))
    {
        client->setModes(MODE_USER_REGISTERED);
        welcome(client, ircServer);
    }
}
