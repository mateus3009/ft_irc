#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include "../Router.hpp"

struct Privmsg
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
