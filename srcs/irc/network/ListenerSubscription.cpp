#include "irc/network/ListenerSubscription.hpp"

/* ListenerSubscription */

ListenerSubscription::ListenerSubscription(
    FileDescriptorObserver& observer,
    SocketListener& listener,
    ConnectionSubscriptionStore& connectionStore)
        :
        Subscription(observer, listener.getId()),
        _listener(&listener),
        _connectionStore(&connectionStore) {}

void ListenerSubscription::handle(const short& events)
{
    if (!(events & POLLIN))
        return ;
    _connectionStore->add(_listener->accept());
}
