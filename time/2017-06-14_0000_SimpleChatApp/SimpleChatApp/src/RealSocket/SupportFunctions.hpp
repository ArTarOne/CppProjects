#pragma once
#include "StdPlus/StdPlus.h"

inline void splitIpAndPort(std::string ipAndPort, std::string & returnHost, uint16_t & returnService)
{
    auto pos = ipAndPort.find_last_of(':');
    if (pos != std::string::npos)
    {
        returnHost = ipAndPort.substr(0, pos);
        std::string strService = ipAndPort.substr(pos + 1);
        std::istringstream iss(strService);
        iss >> returnService;
    }
    else
    {
        returnHost = ipAndPort;
        returnService = 0;
    }
}

inline bool isFile(std::string inputMsg, std::string & returnFilename)
{
    std::vector<std::string> strs = stdplus::split(inputMsg, ':');
    if (strs[0] == "file")
    {
        std::string filePath=strs[1]+":";
        for (unsigned i = 2; i < strs.size(); i++)
            filePath += strs[i];
        returnFilename = filePath;
        return true;
    }

    return false;
}