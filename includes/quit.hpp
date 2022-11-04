#ifndef QUIT_HPP
# define QUIT_HPP

# include "router.hpp"
# include "request.hpp"
# include "response.hpp"
# include "client_store.hpp"

class quit : public route
{
    public:
        quit();

        void handle(const request& req, response& res);
};

#endif
