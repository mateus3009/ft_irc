#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <set>
# include <algorithm>

# include "../utils/shared_ptr.hpp"
# include "utils/Modes.hpp"
# include "Client.hpp"

class Channel;

class Client;

struct Membership : public Modes
{
    private:
        shared_ptr<Client>  _client;

    public:
        Membership(shared_ptr<Client> client, const unsigned int& modes = 0);

        shared_ptr<Client> getClient(void) const;

};

bool operator==(const Membership& l, const Membership& r);

bool operator==(const Membership& m, const Client& c);

bool operator<(const Membership& l, const Membership& r);

class ChannelStore;

class Channel : public Modes
{
    private:
        const std::string                   _name;

        std::string                         _topic;

        std::string                         _key;

        std::set<shared_ptr<Membership> >   _memberships;

        ChannelStore&                       _store;

    public:
        typedef std::set<shared_ptr<Membership> >::iterator iterator;

        Channel(const std::string& name, shared_ptr<Client> founder, ChannelStore& store);

        std::string getName(void) const;

        std::string getTopic(void) const;

        void setTopic(const std::string& topic);

        std::string getKey(void) const;

        void setKey(const std::string& key);

        shared_ptr<Membership> add(shared_ptr<Client> client);

        shared_ptr<Membership> find(shared_ptr<Client> client);

        void remove(shared_ptr<Membership>& client);

        void broadcast(const Message& msg);

        iterator begin(void) const;

        iterator end(void) const;

        struct ClientIsAlreadyAMemberException : public std::runtime_error
        {
            ClientIsAlreadyAMemberException(const char* what);
        };

        struct ClientNotFoundException : public std::runtime_error
        {
            ClientNotFoundException(const char* what);
        };

    private:
        struct ClientMessageSender
        {
            const Message& msg;

            void operator()(shared_ptr<Membership> membership);
        };

};

bool operator==(const Channel& l, const Channel& r);

bool operator==(const Channel& channel, const std::string& name);

bool operator<(const Channel& l, const Channel& r);

class ChannelStore
{
    private:
        std::set<shared_ptr<Channel> >  _channels;

    public:
        typedef std::set<shared_ptr<Channel> >::const_iterator iterator;

        void add(shared_ptr<Client> client, const std::string& name);

        shared_ptr<Channel> find(const std::string& name);

        void remove(const shared_ptr<Channel>& client);

        iterator begin(void) const;

        iterator end(void) const;

        struct ChannelAlreadyExistsException : public std::runtime_error
        {
            ChannelAlreadyExistsException(const char* what);
        };

        struct ChannelNotFoundException : public std::runtime_error
        {
            ChannelNotFoundException(const char* what);
        };

};

#endif
