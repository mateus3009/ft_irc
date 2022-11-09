#include "irc/commands/Part.hpp"

const bool Part::isRegistered = Router::add("PART", Part::handle);

void Part::handle(
    const Message&      msg,
    shared_ptr<Client>& client,
    ClientStore&,
    ChannelStore&       channelStore,
    IrcServer&)
{
    if (!client->hasAnyModes(MODE_USER_REGISTERED))
    {
        client->send(Message() << ERR_NOTREGISTERED << "You have not registered");
        return ;
    }

    if (msg.params.empty())
    {
        client->send(Message() << ERR_NEEDMOREPARAMS << client->getNickname() << "JOIN" << "Not enough parameters");
        return ;
    }

    const std::string& channelName = msg.params.front();

    if (channelName.find(',') != std::string::npos)
    {
        client->send(Message() << ERR_TOOMANYCHANNELS << client->getNickname() << "*" << "You have Left too many channels");
        return ;
    }

    shared_ptr<Channel> channel;

    try
    {
        channel = channelStore.find(channelName);
    }
    catch(const ChannelStore::ChannelNotFoundException&)
    {
        client->send(Message() << ERR_NOSUCHCHANNEL << client->getNickname() << channelName << "No such channel");
        return ;
    }

    shared_ptr<Membership> membership;

    try
    {
        membership = channel->find(client);
    }
    catch(const std::exception& e)
    {
        client->send(Message() << ERR_NOTONCHANNEL<< client->getNickname() << channelName << "You're not on that channel");
        return ;
    }

    channel->remove(membership);

    std::string reason;
    if (msg.params.size() > 1)
        reason = msg.params[1];

    channel->broadcast(Message() << client->getSource() << Verb("PART") << channelName << reason);
}
