#ifndef CHANNEL_STORE_HPP
# define CHANNEL_STORE_HPP

# include <vector>

# include "channel.hpp"

class channel_store
{
    private:
        std::vector<channel> _channels;

    public:
        channel_store(void);

        channel_store(const channel_store& other);

        ~channel_store();

        channel_store& operator=(const channel_store& other);

        //void add(const std::string& channel);

        //void remove(const std::string& channel);

        channel& find(const std::string& channel);
};

#endif
