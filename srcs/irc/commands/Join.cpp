#include "irc/commands/Join.hpp"

const bool Join::isRegistered = Router::add("JOIN", Join::handle);

void Join::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
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
        client->send(Message() << ERR_TOOMANYCHANNELS << client->getNickname() << "*" << "You have joined too many channels");
        return ;
    }

    shared_ptr<Channel> channel;

    try
    {
        channel = channelStore.find(channelName);
    }
    catch(const ChannelStore::ChannelNotFoundException&)
    {
        if (*channelName.begin() != '#')
        {
            client->send(Message() << ERR_NOSUCHCHANNEL << client->getNickname() << channelName << "No such channel");
            return ;
        }

        channelStore.add(client, channelName);
        client->send(Message() << Verb("Mode") << channelName << "+q" << client->getNickname());

        if (msg.params.size() == 2)
            channel->setKey(msg.params[1]);

        return ;
    }

    const std::string& channelKey = channel->getKey();

    if (!channelKey.empty() && (msg.params.size() < 2 || channelKey != msg.params[1]) && !client->hasAnyModes(MODE_USER_OPER))
    {
        client->send(Message() << ERR_BADCHANNELKEY << client->getNickname() << channelName << "Cannot join channel (+k)");
        return ;
    }

    channel->broadcast(Message() << client->getSource() << Verb("JOIN") << channel->getName());
    channel->add(client);
}