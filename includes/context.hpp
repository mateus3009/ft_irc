#ifndef CONTEXT_HPP
# define CONTEXT_HPP

# include "socket_listener.hpp"
# include "socket_server.hpp"

# include "file_descriptor_monitor.hpp"

# include "event_observer.hpp"

# include "connection_observer.hpp"

# include "disconnection_observer.hpp"

# include "message_observer.hpp"

# include "router.hpp"

# include "help.hpp"

void create_irc_context(const char*port);

#endif
