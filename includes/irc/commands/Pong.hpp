#ifndef PONG_HPP
# define PONG_HPP

# include "../Router.hpp"

struct Pong
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
