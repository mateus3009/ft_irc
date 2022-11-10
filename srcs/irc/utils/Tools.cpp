#include "irc/utils/Tools.hpp"

bool    iequals(const std::string& a, const std::string& b)
{
    std::string::const_iterator ita = a.begin();
    std::string::const_iterator itb = b.begin();

    while (ita != a.end() && itb != b.end())
    {
        if (toupper(*ita) != toupper(*itb))
            return false;
        ++ita;
        ++itb;
    }
    return (ita == a.end() && itb == b.end());
}

std::string unixTimestamp(void)
{
    std::stringstream stream;
    std::time_t time = std::time(0);
    stream << time;
    return stream.str();
}

std::vector<std::string> split(const std::string& str, const char delimiter)
{
    std::stringstream stream(str);
    std::vector<std::string> parts;
    std::string part;
    while(std::getline(stream, part, delimiter))
        parts.push_back(part);
    return parts;
}

std::string operator+(const std::string& l, const std::string& r)
{
    return std::string(l).append(r);
}
