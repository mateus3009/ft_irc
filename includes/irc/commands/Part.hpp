#ifndef PART_HPP
# define PART_HPP

# include "../Router.hpp"

struct Part
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
