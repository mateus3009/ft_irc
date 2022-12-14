#ifndef PASS_HPP
# define PASS_HPP

# include "../Router.hpp"
# include "Motd.hpp"

struct Pass
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
