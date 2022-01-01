#pragma once

#include "Application/ISettings.h"

class QSettings;

class SettingUsedQt : public ISettings
{
public:
    SettingUsedQt();
    ~SettingUsedQt();

    virtual std::string get(const std::string & key) override;
    virtual std::string get(const std::string & key, std::string default) override;
    virtual void set(const std::string & key, std::string & value) override;


    virtual void save() override;



private:
    QSettings * m_qSettings = nullptr;
};

