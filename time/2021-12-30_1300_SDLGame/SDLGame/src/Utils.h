#pragma once
#include <string>
#include <fstream>

namespace utils
{
    // https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
    // trim from start (in place)
    inline void leftTrimInPlace(std::string& s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    inline void rightTrimInPlace(std::string& s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    inline void trimInPlace(std::string& s)
    {
        leftTrimInPlace(s);
        rightTrimInPlace(s);
    }

    inline std::string trim(const std::string& s)
    {
        auto copy = s;
        trimInPlace(copy);
        return copy;
    }

    inline bool fileExists(const std::string& name)
    {
        const std::ifstream file(name.c_str());
        return file.good();
    }

    inline std::string deepSearch(const std::string& filename)
    {
        if(fileExists(filename))
        {
            return filename;
        }

        // TODO hardcoded assets folder name
        std::string newFileName = std::string("assets/") + filename;
        _ASSERT(fileExists(newFileName));
        return newFileName;
    }
}
