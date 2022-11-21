#ifndef NICK_HPP
# define NICK_HPP

# include "../Router.hpp"
# include "commons/Welcome.hpp"

struct Nick
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
