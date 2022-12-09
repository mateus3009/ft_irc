#ifndef TOOLS_HPP
# define TOOLS_HPP

# include <vector>
# include <sstream>

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

std::vector<std::string> split(const std::string& str, const char delimiter);

#endif
