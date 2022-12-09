#ifndef CHAT_HPP
# define CHAT_HPP

# include <set>

# include "Client.hpp"

class Client;

class Channel;

struct Membership
{
    private:
        const shared_ptr<Client> _client;

        bool _isFounder;

        bool _isModerator;

    public:
        Membership(shared_ptr<Client> client);

        shared_ptr<Client> getClient(void) const;

        bool isFounder(void) const;

        bool isModerator(void) const;

    friend class Channel;
};

bool operator==(const Membership& l, const std::string& r);

bool operator==(const Membership& l, const Membership& r);

bool operator<(const Membership& l, const Membership& r);

class ChannelStore;

class Channel
{
    private:
        const std::string _name;

        std::string _topic;

        std::string _key;

        std::set<shared_ptr<Membership> > _memberships;

        ChannelStore* _store;
    public:
        Channel(const std::string& name, shared_ptr<Client> founder, ChannelStore& store);

        std::string getName(void) const;

        std::string getTopic(void) const;

        void setTopic(const std::string& topic);

        std::string getKey(void) const;

        void setKey(const std::string& key);

        shared_ptr<Membership> add(shared_ptr<Client> client);

        shared_ptr<Membership> find(const std::string& nickname);

        void remove(const std::string& nickname);

        void broadcast(const Message& msg, const std::string& author = "");

        std::set<shared_ptr<Membership> >::iterator begin(void) const;

        std::set<shared_ptr<Membership> >::iterator end(void) const;

        struct InvalidChannelNameException : public Error
        {
            InvalidChannelNameException(const char* what);
        };

        struct ClientIsAlreadyAMemberException : public Error
        {
            ClientIsAlreadyAMemberException(const char* what);
        };

        struct ClientNotFoundException : public Error
        {
            ClientNotFoundException(const char* what);
        };

};

bool operator==(const Channel& channel, const std::string& name);

bool operator==(const Channel& l, const Channel& r);

bool operator<(const Channel& l, const Channel& r);

class ChannelStore
{
    private:
        std::set<shared_ptr<Channel> >  _channels;

    public:
        shared_ptr<Channel> add(shared_ptr<Client> client, const std::string& name);

        shared_ptr<Channel> find(const std::string& name);

        void remove(const std::string& name);

        std::set<shared_ptr<Channel> >::iterator begin(void);

        std::set<shared_ptr<Channel> >::iterator end(void);

        struct ChannelAlreadyExistsException : public Error
        {
            ChannelAlreadyExistsException(const char* what);
        };

        struct ChannelNotFoundException : public Error
        {
            ChannelNotFoundException(const char* what);
        };

};


#endif
