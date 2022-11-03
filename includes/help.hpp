#ifndef HELP_HPP
# define HELP_HPP

# include <sstream>
# include <iostream>

# include "router.hpp"
# include "request.hpp"
# include "response.hpp"
# include "router.hpp"
# include "client_store.hpp"

# define ERR_HELPNOTFOUND 524
# define RPL_HELPSTART 704
# define RPL_HELPTXT 705
# define RPL_ENDOFHELP 706

class help : public route
{
    private:
        client_store& _store;

    public:
        help(client_store& store);

        void handle(const request& req, response& res);
};

#endif
