#include "channel_store.hpp"

channel_store::channel_store(void) : _channels() {}

channel_store::channel_store(const channel_store& other) : _channels(other._channels) {}

channel_store::~channel_store() {}

channel_store& channel_store::operator=(const channel_store& other)
{
    _channels = other._channels;
    return *this;
}

channel& channel_store::find(const std::string&)
{
    return *_channels.begin();
}
