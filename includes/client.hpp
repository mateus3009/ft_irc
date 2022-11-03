#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <vector>

//# include "channel.hpp"
# include "client_store.hpp"

# define MODE_USER_INVISIBLE    0x01
# define MODE_USER_OPER         0x02
# define MODE_USER_LOCAL_OPER   0x04
# define MODE_USER_REGISTERED   0x08
# define MODE_USER_WALLOPS      0x16

class client_store;

class client
{
    private:
        const int                   _id;

        std::string                 _nickname;

        std::string                 _username;

        const std::string           _hostname;

        int                         _modes;

        //std::vector<const channel*> _channels;

        client_store*               _store;

    public:
        client(const int& id, const std::string& hostname, client_store* store);

        int get_id(void) const;

        std::string get_nickname(void) const;

        bool set_nickname(const std::string& nickname);

        std::string get_username(void) const;

        void set_username(const std::string& username);

        std::string get_hostname(void) const;

        int get_modes(void) const;

        void add_mode(const int& mode);

        void remove_mode(const int& mode);

};

bool operator==(const client& c, const std::string& nickname);

#endif
