#ifndef channel_store_HPP
# define channel_store_HPP

# include "socket_connection.hpp"
# include <string>
# include <vector>
# include "message.hpp"

class channel
{
    private:
        std::string                     _name;
        std::vector<socket_connection>  _clients;

    public:
        channel(void);

        channel(const channel& other);

        ~channel();

        channel& operator=(const channel& other);

        std::string getName(void) const;

        void add(const socket_connection& client);

        void remove(const socket_connection& client);

        void broadcast(const socket_connection& client, const message& msg) const;
};

#endif
