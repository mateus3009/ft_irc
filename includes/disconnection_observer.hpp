#ifndef DISCONNECTION_OBSERVER_HPP
# define DISCONNECTION_OBSERVER_HPP

# include "observer.hpp"
# include "file_descriptor_monitor.hpp"

class disconnection_observer : public observer<const int>
{
    private:
        file_descriptor_monitor& _monitor;

    public:
        disconnection_observer(file_descriptor_monitor& monitor);

        void handle(const int& handler);

};

#endif
