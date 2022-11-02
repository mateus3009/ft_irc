#ifndef HELP_HPP
# define HELP_HPP

# include <sstream>

# include "router.hpp"
# include "request.hpp"
# include "response.hpp"
# include "router.hpp"

# define ERR_HELPNOTFOUND 524
# define RPL_HELPSTART 704
# define RPL_HELPTXT 705
# define RPL_ENDOFHELP 706

class help : public route
{
    public:
        void handle(const request& req, response& res);
};

#endif
