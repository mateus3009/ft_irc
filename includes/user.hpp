#ifndef USER_HPP
# define USER_HPP

# include "router.hpp"
# include "request.hpp"
# include "response.hpp"
# include "client_store.hpp"

class user : public route
{
    private:
        client_store& _store;

    public:
        user(client_store& store);

        void handle(const request& req, response& res);
};

#endif
