#include "irc/commands/Notice.hpp"

const bool Notice::isRegistered = Router::add("NOTICE", Notice::handle);

void Notice::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore& clientStore,
    ChannelStore& channelStore,
    IrcServer& ircServer)
{
    if (!ircServer.isRegistered(client))
        return ;

    if (msg.params.size() < 2)
        return ;

    const std::string& target = msg.params.front();
    const std::string& message = msg.params.back();

    if (target.find(',') != std::string::npos)
        return ;

    if (*target.begin() == '#' || *target.begin() == '&')
    {
        try
        {
            shared_ptr<Channel> channel = channelStore.find(target);
            channel->broadcast(Message() << client->getSource() << Verb("Notice") << target << message);
            return ;
        }
        catch(const ChannelStore::ChannelNotFoundException&)
        {
            return ;
        }
    }

    try
    {
        shared_ptr<Client> clientTarget = clientStore.find(target);
        clientTarget->send(Message() << client->getSource() << Verb("Notice") << target << message);
        return ;
    }
    catch(const ClientStore::ClientNotFoundException&)
    {
    }

}
