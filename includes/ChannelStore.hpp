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

        void add(const SocketConnection& client);

        void remove(const SocketConnection& client);

        void broadcast(const SocketConnection& client,const std::string &msg);
};

/*class ChannelStore
{
    private:
        std::vector<IrcChannel> _channels;

    public:
        ChannelStore(void);

        ChannelStore(const ChannelStore& other);

        ~ChannelStore();

        ChannelStore& operator=(const ChannelStore& other);

        void add(const IrcChannel)
}*/



#endif
