#include "SettingsUsedQt.h"
#include <QSettings>
#include <string>
#include "StdPlus/StdPlus.h"
#include "QtPlus/QtStringPlus.hpp"


SettingUsedQt::SettingUsedQt()
{
    m_qSettings = new QSettings(QSettings::IniFormat,
        QSettings::UserScope, "MarleeeeeeyTeam", "Code Review App");
}

SettingUsedQt::~SettingUsedQt()
{
    delete m_qSettings;
}

std::string SettingUsedQt::get(const std::string & key, std::string default)
{
    QVariant qDefault = QString::fromStdString(default);
    QString qString = m_qSettings->value(QString::fromStdString(key), qDefault).toString();
    m_qSettings->setValue(QString::fromStdString(key), qString);


    std::string value = qtplus::to_string(qString);
    stdplus::trim(value, "\" ");
    return value;    
}

std::string SettingUsedQt::get(const std::string & key)
{
    QVariant ret = m_qSettings->value(QString::fromStdString(key));

    if (!ret.isValid())
        throw std::logic_error("Not value with key " + key);

    std::string value = qtplus::to_string(ret.toString());
    stdplus::trim(value, "\" ");
    return value;
}

void SettingUsedQt::set(const std::string & key, std::string & value)
{
    m_qSettings->setValue(QString::fromStdString(key), QString::fromStdString(value));
}

void SettingUsedQt::save()
{
    // TODO
}
