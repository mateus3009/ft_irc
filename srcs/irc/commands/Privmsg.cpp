#include "irc/commands/Privmsg.hpp"

const bool Privmsg::isRegistered = Router::add("PRIVMSG", Privmsg::handle);

void Privmsg::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore& clientStore,
    ChannelStore& channelStore,
    IrcServer& ircServer)
{
    if (!ircServer.isRegistered(client))
    {
        client->send(Message() << ircServer.getSource() << ERR_NOTREGISTERED << "You have not registered");
        return ;
    }

    if (msg.params.size() < 2)
    {
        client->send(Message() << ircServer.getSource() << ERR_NEEDMOREPARAMS << client->getNickname() << "PRIVMSG" << "Not enough parameters");
        return ;
    }

    const std::string& target = msg.params.front();
    const std::string& message = msg.params.back();

    if (target.find(',') != std::string::npos)
    {
        client->send(Message() << ircServer.getSource() << ERR_TOOMANYTARGETS << client->getNickname() << "*" << "Too many targets");
        return ;
    }

    if (*target.begin() == '#' || *target.begin() == '&')
    {
        try
        {
            shared_ptr<Channel> channel = channelStore.find(target);
            channel->broadcast(Message() << client->getSource() << Verb("PRIVMSG") << target << message);
            return ;
        }
        catch(const ChannelStore::ChannelNotFoundException&)
        {
            client->send(Message() << ircServer.getSource() << ERR_CANNOTSENDTOCHAN << client->getNickname() << target << "No such channel");
            return ;
        }
    }

    try
    {
        shared_ptr<Client> clientTarget = clientStore.find(target);
        clientTarget->send(Message() << client->getSource() << Verb("PRIVMSG") << target << message);
        return ;
    }
    catch(const ClientStore::ClientNotFoundException&)
    {
        client->send(Message() << ircServer.getSource() << ERR_NOSUCHNICK << client->getNickname() << target << "No such nick/channel");
    }

}
