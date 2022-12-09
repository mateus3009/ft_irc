#ifndef LISTENERSUBSCRIPTION_HPP
# define LISTENERSUBSCRIPTION_HPP

# include "../../network/FileDescriptorObserver.hpp"
# include "../../network/Socket.hpp"
# include "ConnectionSubscription.hpp"

class ConnectionSubscriptionStore;

class ListenerSubscription : Subscription
{
    private:
        SocketListener* _listener;

        ConnectionSubscriptionStore* _connectionStore;

    public:
        ListenerSubscription(
            FileDescriptorObserver& observer,
            SocketListener& listener,
            ConnectionSubscriptionStore& connectionStore);

        virtual void handle(const short& events);

};

#endif
