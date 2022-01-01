#include "SettingStdApi.h"




SettingStdApi::SettingStdApi()
{
    std::ifstream fin("Settings.ini");

    if (fin.is_open())
    {
        std::string oneSettingStr;
        while (getline(fin,oneSettingStr))
        {
            std::vector<std::string> keyAndValue = stdplus::split(oneSettingStr, '=');
           
            std::string key=keyAndValue[0];
            std::string value=keyAndValue[1];
            m_userSettings[key] = value;
        }
    }
    else
    {
        std::cout << "No user settings. Settings will be set by default!" << std::endl;
        std::ofstream fout("Settings.ini");
        fout << "path" << "=" << "D:/" << std::endl;
        m_userSettings["path"] = "D:/";
        fout <<"folderMask" << "=" << "*" << std::endl;
        m_userSettings["folderMask"] = "*";
        fout << "fileMask" << "=" << "*.cpp" << std::endl;
        m_userSettings["fileMask"] = "*.cpp";
        fout << "warningFuncSize" << "=" << "30" << std::endl;
        m_userSettings["warningFuncSize"] = "30";
        fout.close();
    }
    fin.close();
}

SettingStdApi::~SettingStdApi()
{
    save();
}

std::string SettingStdApi::get(const std::string & key, std::string default)
{
    auto it = m_userSettings.find(key);

    if (it != m_userSettings.end())
    {
        return it->second;
    }
    else
    {
        set(key, default);
        return default;
    }
}

std::string SettingStdApi::get(const std::string & key)
{
    auto it = m_userSettings.find(key);

    if (it != m_userSettings.end())
    {
        return it->second;
    }
    else
    {
        throw std::logic_error("Not found setting with key " + key);
    }
}

void SettingStdApi::set(const std::string & key, std::string & value)
{
    m_userSettings[key] = value;
}

void SettingStdApi::save()
{
    std::ofstream fout("Settings.ini");

    if (fout.is_open())
    {
        for (auto it = m_userSettings.begin(); it != m_userSettings.end(); it++)
        {
            fout << it->first << "=" << it->second << std::endl;
        }
    }
    else
    {
        std::cout << "Settings not saved" << std::endl;
    }

    fout.close();
}
