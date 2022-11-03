#ifndef CLIENT_STORE_HPP
# define CLIENT_STORE_HPP

# include <string>
# include <map>

# include "client.hpp"
# include "response.hpp"

class client;

class client_store
{
    private:
        std::map<int, client>   _clients;

    public:
        void add(const int& id, const std::string& hostname);

        client* find(const int& id);

        client* find(const std::string& nickname);

        void remove(const int& id);

};

struct client_finder
{
    std::string nickname;

    bool operator()(const std::pair<int, client>& p);
};

#endif
