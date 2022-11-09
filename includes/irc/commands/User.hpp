#ifndef USER_HPP
# define USER_HPP

# include "../Router.hpp"

struct User
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
