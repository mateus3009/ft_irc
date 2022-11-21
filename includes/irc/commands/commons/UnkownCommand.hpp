#ifndef UNKOWNCOMMAND_HPP
# define UNKOWNCOMMAND_HPP

# include "../../Router.hpp"

struct UnkownCommand
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
