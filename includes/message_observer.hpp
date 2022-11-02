#ifndef MESSAGE_OBSERVER_HPP
# define MESSAGE_OBSERVER_HPP

# include <utility>

# include "observer.hpp"
# include "router.hpp"
# include "request.hpp"
# include "response.hpp"

class message_observer : public observer<std::pair<const request, response> >
{
    public:
        void handle(std::pair<const request, response>& rr);
};

#endif

