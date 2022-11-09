#include "network/Server.hpp"
#include "irc/IrcConnection.hpp"
#include "irc/Router.hpp"
#include "irc/Client.hpp"
#include "irc/Channel.hpp"
#include "irc/commands/Help.hpp"
#include <iostream>

int main(int argc, const char** argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[1] << " <port> <pass>" << std::endl;
        return 1;
    }
    ClientStore clientStore;
    ChannelStore channelStore;
    Router::setNotFound(Help::handle);
    Router::setClientStore(&clientStore);
    Router::setChannelStore(&channelStore);
    Server<IrcConnection> server("localhost", "12345");

    server.listen();
    return 0;
}
