#include "client.hpp"

void client_store::add(const int& id, const std::string& hostname)
{
    _clients.insert(std::make_pair(id, client(id, hostname, this)));
}

client* client_store::find(const int& id)
{
    std::map<int, client>::iterator it = _clients.find(id);
    if (it == _clients.end())
        return NULL;
    return &it->second;
}

client* client_store::find(const std::string& nickname)
{
    client_finder finder = { .nickname = nickname };
    std::map<int, client>::iterator it = std::find_if(_clients.begin(), _clients.end(), finder);
    if (it == _clients.end())
        return NULL;
    return &it->second;
}

void client_store::remove(const int& id) { _clients.erase(id); }

bool client_finder::operator()(const std::pair<int, client>& p)
{
    return p.second.get_nickname() == nickname;
}
