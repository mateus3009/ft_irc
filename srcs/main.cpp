#include <iostream>
#include "context.hpp"

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <port> <pass>" << std::endl;
        return (1);
    }

    create_irc_context(argv[1], argv[2]);

    return (0);
}
