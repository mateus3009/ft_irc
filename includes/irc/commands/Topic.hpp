#ifndef TOPIC_HPP
# define TOPIC_HPP

# include "../Router.hpp"

struct Topic
{
    static const bool isRegistered;

    static void handle(
        const Message&      msg,
        shared_ptr<Client>& client,
        ClientStore&        clientStore,
        ChannelStore&       channelStore,
        IrcServer&          server);
};

#endif
