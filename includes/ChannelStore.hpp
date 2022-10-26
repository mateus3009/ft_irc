#ifndef CHANNELSTORE_HPP
# define CHANNELSTORE_HPP

# include "Socket.hpp"
# include <string>
# include <vector>
# include "IrcMessage.hpp"

class IrcChannel
{
    private:
        std::string                     _name;
        std::vector<SocketConnection>   _clients;

    public:
        IrcChannel(void);

        IrcChannel(const IrcChannel& other);

        ~IrcChannel();

        IrcChannel& operator=(const IrcChannel& other);

        std::string getName(void) const;

        void add(const SocketConnection& client);

        void remove(const SocketConnection& client);

        void broadcast(const SocketConnection& client, const IrcMessage& msg) const;
};

class ChannelStore
{
    private:
        std::vector<IrcChannel> _channels;

    public:
        ChannelStore(void);

        ChannelStore(const ChannelStore& other);

        ~ChannelStore();

        ChannelStore& operator=(const ChannelStore& other);

        //void add(const std::string& channel);

        //void remove(const std::string& channel);

        IrcChannel& find(const std::string& channel);
};

#endif
