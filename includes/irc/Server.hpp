#ifndef SERVER_HPP
# define SERVER_HPP

# include "../network/SocketSSL.hpp"
# include "../network/FileDescriptorObserver.hpp"
# include "network/ListenerSubscription.hpp"
# include "network/ConnectionSubscription.hpp"
# include "Client.hpp"
# include "CommandRouter.hpp"
# include "Channel.hpp"

class CommandRouter;

struct ServerContext
{
    std::string motd;

    std::string password;

    std::string serverName;

};

class Server
{
    public:
        Server(const char* port = "0", const char* hostname = NULL, const char* password = "");
};

#endif
