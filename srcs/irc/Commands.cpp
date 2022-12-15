#include "irc/Commands.hpp"

/* Help */

bool Help::isRegistered = CommandRouter::add("HELP", (CommandRegister) {
    .command = Help::handler, .isRegistered = false, .paramsMin = 0});

void Help::handler(Payload& p)
{
    if (p.req.params.empty())
    {
        Message res = p.res << "*";
        p.client->send(res << RPL_HELPSTART << "** Help System **");
        p.client->send(res << RPL_ENDOFHELP << "The commands below are available!");
        for (std::map<std::string, CommandRegister>::iterator it = CommandRouter::_commands.begin(); it != CommandRouter::_commands.end(); ++it)
            p.client->send(res << RPL_ENDOFHELP << it->first);
        p.client->send(res << RPL_ENDOFHELP << "Try /HELP <command> for specific help");
        return ;
    }

    p.client->send(p.res << ERR_HELPNOTFOUND << p.req.params.front() << "No help available on this topic");
}

/* Ping */

bool Ping::isRegistered = CommandRouter::add("PING", (CommandRegister) {
    .command = Ping::handler, .isRegistered = false, .paramsMin = 1});

void Ping::handler(Payload& p)
{
    p.client->send(p.res << Verb("PONG") << p.serverContext->serverName << p.req.params.front());
}

/* Pong */

bool Pong::isRegistered = CommandRouter::add("PONG", (CommandRegister) {
    .command = Pong::handler, .isRegistered = false, .paramsMin = 1});

void Pong::handler(Payload&) {}

/* Quit */

bool Quit::isRegistered = CommandRouter::add("QUIT", (CommandRegister) {
    .command = Quit::handler, .isRegistered = false, .paramsMin = 0});

void Quit::handler(Payload& p)
{
    p.client->send(Message() << p.client->getSource() << Verb("ERROR") << "Bye!");
    p.client->close();

    std::string reason = "Quit: ";
    if (!p.req.params.empty())
        reason = reason + p.req.params.front();

    if (p.client->isRegistered)
        p.clientStore->broadcast(Message() << p.client->getSource() << Verb("QUIT") << p.client->getNickname() << reason, p.client->getNickname());
}

/* Welcome */

static void welcome(shared_ptr<Client>& client, const ServerContext* serverContext)
{
    client->send(Message() << (Message::Source) { .nickname = serverContext->serverName } << RPL_WELCOME << client->getNickname() << "Welcome to the " + serverContext->serverName + " Network, " + client->getSource().toString());
    client->send(Message() << (Message::Source) { .nickname = serverContext->serverName } << RPL_YOURHOST << client->getNickname() << "Your host is " + serverContext->serverName + ", running version 1.0");
    client->send(Message() << (Message::Source) { .nickname = serverContext->serverName } << RPL_CREATED << client->getNickname() << "This server was created 2022-10-14");
    client->send(Message() << (Message::Source) { .nickname = serverContext->serverName } << RPL_MYINFO << client->getNickname() << serverContext->serverName << "1.0" << "+q" << "+i");
    client->send(Message() << (Message::Source) { .nickname = serverContext->serverName } << RPL_ISUPPORT << client->getNickname() << "CASEMAPPING=ascii" << "are supported by this server");
    client->isRegistered = true;
}

/* Pass */

bool Pass::isRegistered = CommandRouter::add("PASS", (CommandRegister) {
    .command = Pass::handler, .isRegistered = false, .paramsMin = 1});

void Pass::handler(Payload& p)
{
    if (p.client->isRegistered || p.client->hasPassword)
        p.client->send(p.res << ERR_ALREADYREGISTERED << "PASS" << "You may not reregister");

    if (p.req.params.front() != p.serverContext->password)
    {
        p.client->send(p.res << ERR_PASSWDMISMATCH << "Password incorrect");
        p.client->send(p.res << Verb("ERROR") << "Password incorrect");
        p.client->close();
        return ;
    }

    p.client->hasPassword = true;

    if (p.client->getNickname() != "*"
        && !p.client->getUsername().empty()
        && !p.client->usingCap)
        welcome(p.client, p.serverContext);
}

/* Nick */

bool Nick::isRegistered = CommandRouter::add("NICK", (CommandRegister) {
    .command = Nick::handler, .isRegistered = false, .paramsMin = 1});

void Nick::handler(Payload& p)
{
    std::string& nickname = p.req.params.front();
    Message::Source olsSource = p.client->getSource();

    try
    {
        p.client->setNickname(nickname);
    }
    catch(const Client::InvalidNicknameException&)
    {
        p.client->send(p.res << ERR_ERRONEUSNICKNAME << nickname << "Erroneus nickname");
        return ;
    }
    catch(const Client::NicknameIsAlreadyInUseException& e)
    {
        p.client->send(p.res << ERR_NICKNAMEINUSE << nickname << "Nickname is already in use");
        return ;
    }

    if (p.client->isRegistered)
        p.clientStore->broadcast(Message() << olsSource << Verb("NICK") << nickname);

    if (!p.client->isRegistered
        && !p.client->getUsername().empty()
        && !p.client->usingCap)
    {
        if (!p.serverContext->password.empty() && !p.client->hasPassword)
        {
            p.client->send(p.res << ERR_PASSWDMISMATCH << "Password was not supplied");
            return ;
        }
        welcome(p.client, p.serverContext);
    }
}

/* User */

bool User::isRegistered = CommandRouter::add("USER", (CommandRegister) {
    .command = User::handler, .isRegistered = false, .paramsMin = 4});

void User::handler(Payload& p)
{
    if (p.client->isRegistered || !p.client->getUsername().empty())
        p.client->send(p.res << ERR_ALREADYREGISTERED << "USER" << "You may not reregister");

    p.client->setUsername(p.req.params[0]);

    p.client->setRealName(p.req.params[3]);

    if (p.client->getNickname() != "*"
        && !p.client->usingCap)
    {
        if (!p.serverContext->password.empty() && !p.client->hasPassword)
        {
            p.client->send(p.res << ERR_PASSWDMISMATCH << "Password was not supplied");
            return ;
        }
        welcome(p.client, p.serverContext);
    }
}

/* Cap */

bool Cap::isRegistered = CommandRouter::add("CAP", (CommandRegister) {
    .command = Cap::handler, .isRegistered = false, .paramsMin = 1});

void Cap::handler(Payload& p)
{
    if (p.client->isRegistered)
        p.clientStore->broadcast(p.res << ERR_ALREADYREGISTERED << "USER" << "You may not reregister");

    const std::string& command = p.req.params.front();

    if (command == "LS")
    {
        p.client->usingCap = true;
        p.client->send(p.res << Verb("CAP") << command << "");
        return ;
    }

    if (command == "END")
    {
        p.client->usingCap = false;
        if (p.client->getNickname() != "*"
            && !p.client->getUsername().empty())
        {
            if (!p.serverContext->password.empty() && !p.client->hasPassword)
            {
                p.client->send(p.res << ERR_PASSWDMISMATCH << "Password was not supplied");
                return ;
            }
            welcome(p.client, p.serverContext);
        }
        return ;
    }

    p.client->send(p.res << ERR_INVALIDCAPCMD << command << "Invalid CAP command");
}

/* Notice */

bool Notice::isRegistered = CommandRouter::add("NOTICE", (CommandRegister) {
    .command = Notice::handler, .isRegistered = true, .paramsMin = 2});

void Notice::handler(Payload& p)
{
    std::vector<std::string> targets = split(p.req.params.front(), ',');
    for (std::vector<std::string>::iterator it = targets.begin();
        it != targets.end(); ++it)
    {
        if (strchr("&#", *it->begin()) != NULL)
        {
            try
            {
                shared_ptr<Channel> c = p.channelStore->find(*it);
                c->broadcast(Message() << p.client->getSource() << Verb("NOTICE") << *it << p.req.params[1], p.client->getNickname());
            }
            catch(const ChannelStore::ChannelNotFoundException&) {}
        }
        else
        {
            try
            {
                shared_ptr<Client> c = p.clientStore->find(*it);
                c->send(Message() << p.client->getSource() << Verb("NOTICE") << *it << p.req.params[1]);
            }
            catch(const ClientStore::ClientNotFoundException&) {}
        }
    }
}

/* Privmsg */

bool Privmsg::isRegistered = CommandRouter::add("PRIVMSG", (CommandRegister) {
    .command = Privmsg::handler, .isRegistered = true, .paramsMin = 2});

void Privmsg::handler(Payload& p)
{
    std::vector<std::string> targets = split(p.req.params.front(), ',');
    for (std::vector<std::string>::iterator it = targets.begin();
        it != targets.end(); ++it)
    {
        try
        {
            if (strchr("&#", *it->begin()) != NULL)
            {
                shared_ptr<Channel> c = p.channelStore->find(*it);
                c->find(p.client->getNickname());
                c->broadcast(Message() << p.client->getSource() << Verb("PRIVMSG") << *it << p.req.params[1], p.client->getNickname());
            }
            else
            {
                shared_ptr<Client> c = p.clientStore->find(*it);
                c->send(Message() << p.client->getSource() << Verb("PRIVMSG") << *it << p.req.params[1]);
            }
        }
        catch(const ChannelStore::ChannelNotFoundException&)
        {
            p.client->send(p.res << ERR_CANNOTSENDTOCHAN << *it << "No such channel");
        }
        catch(const Channel::ClientNotFoundException&)
        {
            p.client->send(p.res << ERR_NOTONCHANNEL << *it << "You're not on that channel");
        }
        catch(const ClientStore::ClientNotFoundException&)
        {
            p.client->send(p.res << ERR_NOSUCHNICK << *it << "No such nick/channel");
        }
    }
}

/* Motd */

bool Motd::isRegistered = CommandRouter::add("MOTD", (CommandRegister) {
    .command = Motd::handler, .isRegistered = true, .paramsMin = 0});

void Motd::handler(Payload& p)
{
    if (p.serverContext->motd.empty())
    {
        p.client->send(p.res << ERR_NOMOTD << "MOTD File is missing");
        return ;
    }

    p.client->send(p.res << RPL_MOTDSTART << "- " + p.serverContext->serverName + " Message of the day -");
    p.client->send(p.res << RPL_MOTD << p.serverContext->motd);
    p.client->send(p.res << RPL_ENDOFMOTD << "End of /MOTD command.");
}

/* Mode */

bool Mode::isRegistered = CommandRouter::add("MODE", (CommandRegister) {
    .command = Mode::handler, .isRegistered = true, .paramsMin = 0});

void Mode::handler(Payload& p)
{
    if (p.req.params.size() == 0)
    {
        p.client->send(p.res << RPL_UMODEIS << "ir");
        return ;
    }

    if (p.req.params.size() <= 2)
    {
        const std::string& target = p.req.params.front();
        try
        {
            if (strchr("&#", *target.begin()) != NULL)
            {
                shared_ptr<Channel> c = p.channelStore->find(target);
                p.client->send(p.res << RPL_UMODEIS << (c->getKey().empty() ? "tn" : "tnk"));
            }
            else
            {
                shared_ptr<Client> c = p.clientStore->find(target);
                p.client->send(p.res << RPL_UMODEIS << "ir");
            }
        }
        catch(const ChannelStore::ChannelNotFoundException&)
        {
            p.client->send(p.res << ERR_CANNOTSENDTOCHAN << target << "No such channel");
        }
        catch(const ClientStore::ClientNotFoundException&)
        {
            p.client->send(p.res << ERR_NOSUCHNICK << target << "No such nick/channel");
        }
        return ;
    }

    p.client->send(p.res << ERR_UNKNOWNERROR << "MODE" << "command/subcommand could not be processed.");
}

/* Whois */

bool Whois::isRegistered = CommandRouter::add("WHOIS", (CommandRegister) {
    .command = Whois::handler, .isRegistered = true, .paramsMin = 1});

void Whois::handler(Payload& p)
{
    std::string& target = p.req.params.back();
    try
    {
        shared_ptr<Client> c = p.clientStore->find(target);
        p.client->send(p.res << RPL_WHOISUSER << target << c->getUsername() << c->getHostname() << "*" << c->getRealName());
        p.client->send(p.res << RPL_WHOISSPECIAL << target << "It is a client!");

    }
    catch(const ClientStore::ClientNotFoundException&)
    {
        p.client->send(p.res << ERR_NOSUCHNICK << target << "No such nick/channel");
    }
    p.client->send(p.res << RPL_ENDOFWHOIS << "End of /WHOIS list");
}

/* Join */

bool Join::isRegistered = CommandRouter::add("JOIN", (CommandRegister) {
    .command = Join::handler, .isRegistered = true, .paramsMin = 1});

void Join::handler(Payload& p)
{
    if (p.req.params.size() == 1 && p.req.params.front() == "0")
    {
        for (std::set<shared_ptr<Channel> >::iterator it = p.channelStore->begin(); it != p.channelStore->end(); ++it)
        {
            try
            {
                shared_ptr<Channel> c = *it;
                c->find(p.client->getNickname());
                c->broadcast(Message() << p.client->getSource() << Verb("PART") << c->getName() << "Reason: Leaving all channels");
                c->remove(p.client->getNickname());
            }
            catch(const ChannelStore::ChannelNotFoundException&) {}
            catch(const Channel::ClientNotFoundException&) {}
        }
        return ;
    }

    std::vector<std::string> targets = split(p.req.params.front(), ',');
    std::vector<std::string> passwords(targets.size());
    if (p.req.params.size() > 1)
        passwords = split(p.req.params[1], ',');
    passwords.resize(targets.size());

    if (targets.size() > 5)
    {
        p.client->send(p.res << ERR_TOOMANYCHANNELS <<  "*" << "You have joined too many channels");
        return ;
    }

    for (size_t index = 0; index < targets.size(); ++index)
    {
        try
        {
            shared_ptr<Channel> c = p.channelStore->find(targets[index]);
            if (c->getKey() == passwords[index] || p.client->isOperator)
            {
                c->add(p.client);

                c->broadcast(Message() << p.client->getSource() << Verb("JOIN") << targets[index], p.client->getNickname());

                if (!c->getTopic().empty())
                    p.client->send(p.res << RPL_TOPIC << c->getTopic());
                for (std::set<shared_ptr<Membership> >::iterator it = c->begin(); it != c->end(); ++it)
                    p.client->send(p.res << RPL_NAMREPLY  << "=" << c->getName() << (*it)->getClient()->getNickname());
                p.client->send(p.res << RPL_ENDOFNAMES << c->getName() << "End of /NAMES list");
                return ;
            }

            p.client->send(p.res << ERR_BADCHANNELKEY << targets[index] << "Cannot join channel (+k)");
        }
        catch(const ChannelStore::ChannelNotFoundException&)
        {
            try
            {
                shared_ptr<Channel> c = p.channelStore->add(p.client, targets[index]);
                c->setKey(passwords[index]);
                p.client->send(p.res << Verb("Mode") << targets[index] << "+q" << p.client->getNickname());
                for (std::set<shared_ptr<Membership> >::iterator it = c->begin(); it != c->end(); ++it)
                    p.client->send(p.res << RPL_NAMREPLY  << "=" << c->getName() << (*it)->getClient()->getNickname());
                p.client->send(p.res << RPL_ENDOFNAMES << c->getName() << "End of /NAMES list");
            }
            catch(const Channel::InvalidChannelNameException&)
            {
                p.client->send(p.res << ERR_NOSUCHCHANNEL << targets[index] << "No such channel");
            }
        }
        catch (const Channel::ClientIsAlreadyAMemberException&)
        {
            p.client->send(p.res << ERR_USERONCHANNEL << p.client->getNickname() << targets[index] << "is already on channel");
        }
    }
}

/* Topic */

bool Topic::isRegistered = CommandRouter::add("TOPIC", (CommandRegister) {
    .command = Topic::handler, .isRegistered = true, .paramsMin = 1});

void Topic::handler(Payload& p)
{
    std::string& target = p.req.params.front();
    try
    {
        shared_ptr<Channel> c = p.channelStore->find(target);
        shared_ptr<Membership> m;
        if (!p.client->isOperator)
            m = c->find(p.client->getNickname());
        if (p.req.params.size() > 1)
        {
            if (!p.client->isOperator && !m->isFounder())
            {
                p.client->send(p.res << ERR_CHANOPRIVSNEEDED << target << "You're not channel operator");
                return ;
            }
            c->setTopic(p.req.params[1]);
        }
        if (c->getTopic().empty())
            p.client->send(p.res << RPL_NOTOPIC << target << "No topic is set");
        else
            p.client->send(p.res << RPL_TOPIC << target << c->getTopic());
    }
    catch(const ChannelStore::ChannelNotFoundException&)
    {
        p.client->send(p.res << ERR_NOSUCHCHANNEL << target << "No such channel");
    }
    catch(const Channel::ClientNotFoundException&)
    {
        p.client->send(p.res << ERR_NOTONCHANNEL << target << "You're not on that channel");
    }
}

/* Part */

bool Part::isRegistered = CommandRouter::add("PART", (CommandRegister) {
    .command = Part::handler, .isRegistered = true, .paramsMin = 1});

void Part::handler(Payload& p)
{
    std::vector<std::string> targets = split(p.req.params.front(), ',');
    std::string reason = "";
    if (p.req.params.size() > 1)
        reason = reason + p.req.params[1];
    for (std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); ++it)
    {
        try
        {
            shared_ptr<Channel> c = p.channelStore->find(*it);
            c->find(p.client->getNickname());
            c->broadcast(Message() << p.client->getSource() << Verb("PART") << *it << reason);
            c->remove(p.client->getNickname());
        }
        catch(const ChannelStore::ChannelNotFoundException&)
        {
            p.client->send(p.res << ERR_NOSUCHCHANNEL << *it << "No such channel");
        }
        catch(const Channel::ClientNotFoundException&)
        {
            p.client->send(p.res << ERR_NOTONCHANNEL << *it << "You're not on that channel");
        }
    }
}

/* Who */

bool Who::isRegistered = CommandRouter::add("WHO", (CommandRegister) {
    .command = Who::handler, .isRegistered = true, .paramsMin = 1});

void Who::handler(Payload& p)
{
    std::string& target = p.req.params.front();
    try
    {
        if (strchr("&#", *target.begin()) != NULL)
        {
            shared_ptr<Channel> c = p.channelStore->find(target);
            c->find(p.client->getNickname());
            for (std::set<shared_ptr<Membership> >::iterator it = c->begin(); it != c->end(); ++it)
            {
                shared_ptr<Client> client = (*it)->getClient();
                p.client->send(p.res << RPL_WHOREPLY << c->getName()
                << client->getUsername() << client->getHostname()
                << p.serverContext->serverName << client->getNickname()
                << "H" << "0 " + client->getRealName());
            }
        }
        else
        {
            shared_ptr<Client> c = p.clientStore->find(target);
            p.client->send(p.res << RPL_WHOREPLY << "*"
                << p.client->getUsername() << p.client->getHostname()
                << p.serverContext->serverName << p.client->getNickname()
                << "H" << "0 " + p.client->getRealName());
        }
        p.client->send(p.res << RPL_ENDOFWHO << target << "End of WHO list");
    }
    catch(const ChannelStore::ChannelNotFoundException&)
    {
        p.client->send(p.res << ERR_NOSUCHCHANNEL << target << "No such channel");
    }
    catch(const Channel::ClientNotFoundException&)
    {
        p.client->send(p.res << ERR_NOTONCHANNEL << target << "You're not on that channel");
    }
    catch(const ClientStore::ClientNotFoundException&)
    {
        p.client->send(p.res << ERR_NOSUCHNICK << target << "No such nick/channel");
    }
}

/* Oper */

bool Oper::isRegistered = CommandRouter::add("OPER", (CommandRegister) {
    .command = Oper::handler, .isRegistered = true, .paramsMin = 2});

void Oper::handler(Payload& p)
{
    if (p.serverContext->operName != p.req.params[0]
        || p.serverContext->operPassword != p.req.params[1])
    {
        p.client->send(p.res << ERR_PASSWDMISMATCH << "Password incorrect");
        return ;
    }
    p.client->isOperator = true;
    p.client->send(p.res << RPL_YOUREOPER << "You are now an IRC operator");
    p.client->send(p.res << RPL_UMODEIS << "iro");
}

/* Kill */

bool Kill::isRegistered = CommandRouter::add("KILL", (CommandRegister) {
    .command = Kill::handler, .isRegistered = true, .isOperator = true, .paramsMin = 1});

void Kill::handler(Payload& p)
{
    std::string& target = p.req.params.front();
    std::string reason = "";
    if (p.req.params.size() > 1)
        reason = reason + p.req.params[1];
    try
    {
        shared_ptr<Client> c = p.clientStore->find(target);
        p.clientStore->broadcast(Message() << c->getSource() << Verb("QUIT") << c->getNickname() << "Killed " + p.client->getNickname() + " " + reason);
        c->send(Message() << p.client->getSource() << Verb("ERROR") << reason);
        c->close();
    }
    catch(const ClientStore::ClientNotFoundException&)
    {
        p.client->send(p.res << ERR_NOSUCHNICK << target << "No such nick/channel");
    }
}
