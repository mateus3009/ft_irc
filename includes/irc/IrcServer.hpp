#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <string>

# include "Message.hpp"
# include "Client.hpp"

class Client;

class IrcServer
{
    private:
        std::string _motd;

        std::string _password;

        std::string _serverName;

        std::string _welcomeMessage;

    public:
        IrcServer(void);

        std::string getMotd(void) const;

        void setMotd(const std::string& motd);

        std::string getPassword(void) const;

        void setPassword(const std::string& password);

        std::string getServerName(void) const;

        void setServerName(const std::string& serverName);

        std::string getWelcomeMessage(void) const;

        void setWelcomeMessage(const std::string& welcomeMessage);

        Message::Source getSource(void) const;

        bool isRegistered(shared_ptr<Client> client) const;
};

#endif
