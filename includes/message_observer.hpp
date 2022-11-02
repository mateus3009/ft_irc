#ifndef MESSAGE_OBSERVER_HPP
# define MESSAGE_OBSERVER_HPP

# include <utility>

# include "observer.hpp"
# include "router.hpp"
# include "request.hpp"
# include "response.hpp"
# include "router.hpp"

class message_observer : public observer<std::pair<const request, response> >
{
    private:
        router* _router;

    public:
        message_observer(router* router);

        void handle(std::pair<const request, response>& rr);
};

#endif

