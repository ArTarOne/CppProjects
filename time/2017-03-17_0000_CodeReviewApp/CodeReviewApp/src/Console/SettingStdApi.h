#pragma once

#include "Application/ISettings.h"

class SettingStdApi : public ISettings
{
public:
    SettingStdApi();
    ~SettingStdApi();

    virtual std::string get(const std::string & key) override;
    virtual std::string get(const std::string & key, std::string default) override;
    virtual void set(const std::string & key, std::string & value) override;


    virtual void save() override;



private:
    std::map<std::string, std::string >m_userSettings;
};

