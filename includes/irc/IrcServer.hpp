#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <string>

# include "Message.hpp"

class IrcServer
{
    private:
        std::string _motd;

        std::string _password;

        std::string _serverName;

    public:
        IrcServer(void);

        std::string getMotd(void) const;

        void setMotd(const std::string& motd);

        std::string getPassword(void) const;

        void setPassword(const std::string& password);

        std::string getServerName(void) const;

        void setServerName(const std::string& serverName);

        Message::Source getSource(void) const;
};

#endif
