#include <iostream>
#include "context.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return (1);
    }

    create_irc_context(argv[1]);

    return (0);
}
