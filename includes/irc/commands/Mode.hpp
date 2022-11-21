#ifndef MODE_HPP
# define MODE_HPP

# include <string>

# include "../Router.hpp"
# include "commons/Welcome.hpp"

# define USERMODES_SIZE 5
# define CHANNELMODES_SIZE 9

struct ModeParse
{
    unsigned int    id;
    unsigned char   symbol;
};

struct Mode
{
    static const bool isRegistered;

    static const ModeParse* userModes;

    static const ModeParse* channelModes;

    static void handle(
        const Message&      msg,
        shared_ptr<Client>  client,
        ClientStore&        clientStore,
        ChannelStore&       channelStore,
        IrcServer&          server);

    static std::string toString(unsigned int modes, const ModeParse* collection, size_t len);
};

#endif
