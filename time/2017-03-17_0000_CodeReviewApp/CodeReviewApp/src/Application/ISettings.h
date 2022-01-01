#pragma once

#include "StdPlus/StdPlus.h"

class ISettings
{
public:    
    void operator=(const ISettings &) = delete;
    virtual ~ISettings() {}

    virtual std::string get(const std::string & key) = 0;
    virtual std::string get(const std::string & key, std::string default) = 0;
    virtual void set(const std::string & key, std::string & value) = 0;  
    virtual void save() = 0;
};

