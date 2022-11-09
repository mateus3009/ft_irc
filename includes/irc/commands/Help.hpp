#ifndef HELP_HPP
# define HELP_HPP

# include "../Router.hpp"

struct Help
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
