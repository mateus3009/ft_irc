#ifndef CLIENT_STORE_HPP
# define CLIENT_STORE_HPP

# include <string>
# include <map>

# include "client.hpp"
# include "response.hpp"

class client_store
{
    private:
        static client_store     _store;

        std::map<int, client>   _clients;

    public:
        static client_store* get(void);

        void create(const int& id, const std::string& hostname);

        void remove(const int& id);

        client* get(const int& id);

        void rename(const int& id, std::string& nick)
};

#endif
