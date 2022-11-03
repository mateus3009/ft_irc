#ifndef DISCONNECTION_OBSERVER_HPP
# define DISCONNECTION_OBSERVER_HPP

# include "observer.hpp"
# include "file_descriptor_monitor.hpp"
# include "client_store.hpp"

class disconnection_observer : public observer<const int>
{
    private:
        file_descriptor_monitor& _monitor;

        client_store& _store;

    public:
        disconnection_observer(file_descriptor_monitor& monitor, client_store& store);

        void handle(const int& id);

};

#endif
