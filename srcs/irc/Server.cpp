#include "irc/Server.hpp"

/* Server */

Server::Server(const char* port, const char* hostname, const char* password)
{
    SocketListener socketListener(port, hostname);

    ClientStore clientStore;

    ChannelStore channelStore;

    FileDescriptorObserver fileDescriptorObserver;

    ConnectionSubscriptionStore connectionSubscriptionStore(
        fileDescriptorObserver, clientStore);

    ListenerSubscription listenerSubscription(
        fileDescriptorObserver, socketListener, connectionSubscriptionStore);

    CommandRouter::clientStore = &clientStore;

    CommandRouter::channelStore = &channelStore;

    ServerContext sctx = (ServerContext) {
        .motd = "Hello world",
        .password = std::string(password),
        .serverName = "42irc"
    };

    CommandRouter::serverContext = &sctx;

    std::cout << "Server listenning on port " << Socket::getPort(socketListener.getsockname()) << std::endl;

    fileDescriptorObserver.start();
}
