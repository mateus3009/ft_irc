#ifndef TOOLS_HPP
# define TOOLS_HPP

# include <string>
# include <cctype>
# include <ctime>
# include <sstream>
# include <vector>
# include <iterator>

bool iequals(const std::string& a, const std::string& b);

template <typename ITER, typename P>
bool    allOf(ITER begin, ITER end, P predicate )
{
    while (begin != end)
    {
        if (!predicate(*begin))
            return false;
        ++begin;
    }
    return true;
};

std::string unixTimestamp(void);

std::vector<std::string> split(const std::string& str, const char delimiter = ',');

#endif
