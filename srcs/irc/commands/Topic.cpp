#include "irc/commands/Topic.hpp"

const bool Topic::isRegistered = Router::add("TOPIC", Topic::handle);

void Topic::handle(
    const Message&      msg,
    shared_ptr<Client>  client,
    ClientStore&,
    ChannelStore&       channelStore,
    IrcServer&          ircServer)
{
    if (!ircServer.isRegistered(client))
    {
        client->send(Message() << ircServer.getSource() << ERR_NOTREGISTERED << "You have not registered");
        return ;
    }

    if (msg.params.empty())
    {
        client->send(Message() << ircServer.getSource() << ERR_NEEDMOREPARAMS << client->getNickname() << "TOPIC" << "Not enough parameters");
        return ;
    }

    const std::string& target = *msg.params.begin();
    shared_ptr<Channel> channel;

    try
    {
        channel = channelStore.find(target);
    }
    catch(const ChannelStore::ChannelNotFoundException& e)
    {
        client->send(Message() << ircServer.getSource() << ERR_NOSUCHCHANNEL << client->getNickname() << target << "No such channel");
        return ;
    }

    shared_ptr<Membership> membership;

    if (!client->hasAnyModes(MODE_USER_OPER))
    {
        try
        {
            membership = channel->find(client);
        }
        catch(const std::exception& e)
        {
            client->send(Message() << ircServer.getSource() << ERR_NOTONCHANNEL << client->getNickname() << target << "You're not on that channel");
            return ;
        }
    }

    const std::string topic = channel->getTopic();

    if (msg.params.size() == 1)
    {
        if (topic.empty())
        {
            client->send(Message() << ircServer.getSource() << RPL_NOTOPIC << client->getNickname() << target << "No topic is set");
            return ;
        }

        client->send(Message() << ircServer.getSource() << RPL_TOPIC << client->getNickname() << target << topic);
        return ;
    }

    if (!membership->hasAnyModes(MODE_MEMBERSHIP_FOUNDER | MODE_MEMBERSHIP_OPERATOR) && !client->hasAnyModes(MODE_USER_OPER))
    {
        client->send(Message() << ircServer.getSource() << ERR_CHANOPRIVSNEEDED << client->getNickname() << target << "You're not channel operator");
        return ;
    }

    channel->setTopic(topic);
    channel->broadcast(Message() << ircServer.getSource() << RPL_TOPIC << client->getNickname() << target << topic);
    channel->broadcast(Message() << ircServer.getSource() << RPL_TOPICWHOTIME  << client->getNickname() << target << client->getNickname() << unixTimestamp());
}
