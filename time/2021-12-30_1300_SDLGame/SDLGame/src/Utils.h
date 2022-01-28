#pragma once
#include <string>

namespace utils
{
// https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
// trim from start (in place)
inline void ltrimInPlace(std::string& s)
{
    s.erase(s.begin(),
            std::find_if(s.begin(),
                         s.end(),
                         [](unsigned char ch)
                         {
                             return !std::isspace(ch);
                         }));
}

// trim from end (in place)
inline void rtrimInPlace(std::string& s)
{
    s.erase(std::find_if(s.rbegin(),
                         s.rend(),
                         [](unsigned char ch)
                         {
                             return !std::isspace(ch);
                         }).base(),
            s.end());
}

// trim from both ends (in place)
inline void trimInPlace(std::string& s)
{
    ltrimInPlace(s);
    rtrimInPlace(s);
}

inline std::string trim(const std::string& s)
{
    auto copy = s;
    trimInPlace(copy);
    return copy;
}
}
