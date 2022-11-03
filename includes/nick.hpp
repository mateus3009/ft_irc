#ifndef NICK_HPP
# define NICK_HPP

# include "router.hpp"
# include "request.hpp"
# include "response.hpp"
# include "client_store.hpp"

# define ERR_NONICKNAMEGIVEN    431
# define ERR_ERRONEUSNICKNAME   432
# define ERR_NICKNAMEINUSE      433
# define ERR_NICKCOLLISION      436

class nick : public route
{
    private:
        client_store& _store;

    public:
        nick(client_store& store);

        void handle(const request& req, response& res);
};

#endif
