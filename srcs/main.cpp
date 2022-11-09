#include "network/Server.hpp"
#include "irc/IrcConnection.hpp"
#include "irc/Router.hpp"
#include "irc/Client.hpp"
#include "irc/Channel.hpp"
#include "irc/IrcServer.hpp"
#include "irc/commands/Help.hpp"
#include <iostream>

int main(int argc, const char** argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <port> <pass>" << std::endl;
        return 1;
    }
    ClientStore clientStore;
    ChannelStore channelStore;
    IrcServer ircServer;
    ircServer.setPassword(argv[2]);
    ircServer.setServerName("42irc");
    Router::setNotFound(Help::handle);
    Router::setClientStore(&clientStore);
    Router::setChannelStore(&channelStore);
    Router::setIrcServer(&ircServer);
    Server<IrcConnection> server("localhost", argv[1]);

    server.listen();
    return 0;
}
