#ifndef HELP_HPP
# define HELP_HPP

# include <sstream>

# include "router.hpp"
# include "request.hpp"
# include "response.hpp"

class help
{
    private:
        static bool is_registered;

    public:
        static void route(request& req, response& res);
};

#endif
