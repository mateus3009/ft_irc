#include "channel_store.hpp"

channel& channel_store::find(const std::string&)
{
    return *_channels.begin();
}
