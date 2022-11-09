#ifndef JOIN_HPP
# define JOIN_HPP

# include <algorithm>
# include <iterator>

# include "../Router.hpp"

struct Join
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
