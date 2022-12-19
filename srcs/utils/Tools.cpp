#include "utils/Tools.hpp"

std::vector<std::string> split(const std::string& str, const char delimiter)
{
    std::stringstream stream(str);
    std::vector<std::string> parts;
    std::string part;
    while(std::getline(stream, part, delimiter))
        parts.push_back(part);
    return parts;
}
