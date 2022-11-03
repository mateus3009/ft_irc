#include "client.hpp"

client::client(const int& id, const std::string& hostname, client_store* store) :
    _id(id),
    _nickname(),
    _username(),
    _hostname(hostname),
    _modes(0),
   // _channels(),
    _store(store) {}

int client::get_id(void) const { return _id; }

std::string client::get_nickname(void) const { return _nickname; }

bool client::set_nickname(const std::string& nickname)
{
    if (_store->find(nickname) != NULL)
        return false;
    _nickname = nickname;
    return true;
}

std::string client::get_username(void) const { return _username; }

void client::set_username(const std::string& username) { _username = username; }

std::string client::get_hostname(void) const { return _hostname; }

int client::get_modes(void) const { return _modes; }

void client::add_mode(const int& mode) { _modes |= mode; }

void client::remove_mode(const int& mode) { _modes &= ~mode; }

bool operator==(const client& c, const std::string& nickname)
{
    return c.get_nickname() == nickname;
}
