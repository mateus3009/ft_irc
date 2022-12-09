#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <map>
# include <string>
# include <algorithm>

# include "Message.hpp"
# include "../utils/shared_ptr.hpp"
# include "../network/Socket.hpp"
# include "../utils/Tools.hpp"
# include "network/ConnectionSubscription.hpp"

class ClientStore;

class ConnectionSubscription;

class Client
{
    private:
        ClientStore* _store;

        ConnectionSubscription* _connection;

        std::string _nickname;

        std::string _username;

        std::string _hostname;

        std::string _realName;

    protected:
        Client(ClientStore& store, ConnectionSubscription& connection);

    public:
        bool isRegistered;

        bool hasPassword;

        bool usingCap;

        std::string getNickname(void) const;

        void setNickname(const std::string& nickname);

        std::string getUsername(void) const;

        void setUsername(const std::string& username);

        std::string getHostname(void) const;

        void setHostname(const std::string& hostname);

        std::string getRealName(void) const;

        void setRealName(const std::string& realName);

        void send(const Message& msg);

        int getId(void) const;

        void close(void);

        Message::Source getSource(void) const;

    public:
        struct InvalidNicknameException : public Error
        {
            InvalidNicknameException(const char* what);
        };

        struct NicknameIsAlreadyInUseException : public Error
        {
            NicknameIsAlreadyInUseException(const char* what);
        };

        struct AlreadyDefinedException : public Error
        {
            AlreadyDefinedException(const char* what);
        };

    friend class ClientStore;
};

bool operator==(const Client& c, const std::string n);

class ClientStore
{
    private:
        std::map<int, shared_ptr<Client> >  _clients;

    public:
        shared_ptr<Client> add(ConnectionSubscription& connection);

        void remove(const int& id);

        shared_ptr<Client> find(const std::string& nickname);

        void broadcast(const Message& msg, const std::string& author = "");

    public:
        struct ClientAlreadyExistsException : public Error
        {
            ClientAlreadyExistsException(const char* what);
        };

        struct ClientNotFoundException : public Error
        {
            ClientNotFoundException(const char* what);
        };

    private:
        struct NicknamePredicate
        {
            const std::string& nickname;

            bool operator()(std::pair<int, shared_ptr<Client> > item);
        };

};

#endif
