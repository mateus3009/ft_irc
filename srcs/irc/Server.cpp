#include "irc/Server.hpp"

/* Server */

Server::Server(const char* port, const char* hostname, const char* password)
{
    SocketListener socketListener(port, hostname);
    init(socketListener, password);
}

void Server::init(const SocketListener& listener, const std::string& password)
{
    ClientStore clientStore;

    ChannelStore channelStore;

    FileDescriptorObserver fileDescriptorObserver;

    ConnectionSubscriptionStore connectionSubscriptionStore(
        fileDescriptorObserver, clientStore);

    ListenerSubscription listenerSubscription(
        fileDescriptorObserver, listener, connectionSubscriptionStore);

    CommandRouter::clientStore = &clientStore;

    CommandRouter::channelStore = &channelStore;

    ServerContext sctx = (ServerContext) {
        .motd = "Hello world",
        .password = password,
        .serverName = "42irc",
        .operName = "42oper",
        .operPassword = "1234"
    };

    CommandRouter::serverContext = &sctx;

    std::cout << "Server listenning on port " << Socket::getPort(listener.getsockname()) << std::endl;

    fileDescriptorObserver.start();
}
