#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <map>
# include <string>
# include <stdexcept>
# include <string>

# include "Message.hpp"
# include "../utils/shared_ptr.hpp"
# include "utils/Tools.hpp"
# include "utils/Modes.hpp"
# include "IrcConnection.hpp"
# include "Channel.hpp"

class IrcConnection;

class ClientStore;

class Client : public Modes
{
    private:
        std::string         			_nickname;

        std::string         			_username;

        const std::string   			_hostname;

        std::string         			_realName;

        IrcConnection&      			_connection;

        ClientStore&        			_store;

		std::set<std::string>			_channels;

    public:
        Client(const std::string& hostname, IrcConnection& connection, ClientStore& store);

        std::string getNickname(void) const;

        void setNickname(const std::string& nickname);

        std::string getUsername(void) const;

        void setUsername(const std::string& username);

        std::string getHostname(void) const;

        std::string getRealName(void) const;

        void setRealName(const std::string& realName);

        void send(const Message& msg);

        void close(void);

		bool addChannel(std::string ch);

        Message::Source getSource(void) const;

        struct AlphaNumericConstraintViolationException : public std::runtime_error
        {
            AlphaNumericConstraintViolationException(const char* what);
        };

        struct NicknameIsAlreadyInUseException : public std::runtime_error
        {
            NicknameIsAlreadyInUseException(const char* what);
        };

        struct UsernameIsAlreadyDefinedException : public std::runtime_error
        {
            UsernameIsAlreadyDefinedException(const char* what);
        };

};

bool operator==(const Client& l, const Client& r);

bool operator==(const Client& client, const std::string& nickname);

bool operator<(const Client& l, const Client& r);

class ClientStore
{
    private:
        std::map<int, shared_ptr<Client> >   _clients;

    public:
        typedef std::map<int, shared_ptr<Client> >::iterator iterator;

        shared_ptr<Client> add(const int& id, const std::string& hostname, IrcConnection& connection);

        shared_ptr<Client> find(const std::string& nickname);

        void broadcast(const Message& msg);

        void remove(shared_ptr<Client> client);

        struct ClientNotFoundException : public std::runtime_error
        {
            ClientNotFoundException(const char* what);
        };

        struct ClientAlreadyExists : public std::runtime_error
        {
            ClientAlreadyExists(const char* what);
        };

    private:
        struct NicknamePredicate
        {
            const std::string& nickname;

            bool operator()(std::pair<int, shared_ptr<Client> > item);
        };

        struct ClientPredicate
        {
            shared_ptr<Client> client;

            bool operator()(std::pair<int, shared_ptr<Client> > item);
        };

        struct ClientMessageSender
        {
            const Message& msg;

            void operator()(std::pair<int, shared_ptr<Client> > item);
        };

};

#endif
