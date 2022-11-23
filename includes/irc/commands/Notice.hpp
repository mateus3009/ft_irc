#ifndef NOTICE_HPP
# define NOTICE_HPP

# include "../Router.hpp"

struct Notice
{
    static const bool isRegistered;

    static void handle(
        const Message&      msg,
        shared_ptr<Client>  client,
        ClientStore&        clientStore,
        ChannelStore&       channelStore,
        IrcServer&          server);
};

#endif
