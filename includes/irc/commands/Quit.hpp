#ifndef QUIT_HPP
# define QUIT_HPP

# include "../Router.hpp"

struct Quit
{
    static const bool isRegistered;

    static void handle(
        const Message&      msg,
        shared_ptr<Client>& client,
        ClientStore&        clientStore,
        ChannelStore&       channelStore);
};

#endif
