#ifndef MOTD_HPP
# define MOTD_HPP

# include "../Router.hpp"

struct Motd
{
    static const bool isRegistered;

    static void handle(
        const Message&      msg,
        shared_ptr<Client>  client,
        ClientStore&        clientStore,
        ChannelStore&       channelStore,
        IrcServer&          server);

    static void showMotd(
        shared_ptr<Client>  client,
        IrcServer&          server);

};

#endif
