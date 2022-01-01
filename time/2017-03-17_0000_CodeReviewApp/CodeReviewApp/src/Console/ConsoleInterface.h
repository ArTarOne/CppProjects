#pragma once
#include "Application/IUserInterface.h"

class ConsoleInterface : public IUserInterface
{
public:
    ConsoleInterface();
    ~ConsoleInterface();
    virtual void setFuncs(const FuncInfoContainer & funcs) override;
    virtual void resetFuncs() override; 
    virtual void setCommands(Commands & commands) override;    
    virtual void resetCommands() override;    
    virtual void show() override;    
    virtual void setSettings(ISettings * settings) override;
private:
    Commands *                m_ptrCommands = nullptr;
    const FuncInfoContainer * m_funcs = nullptr;
    ISettings *               m_settings = nullptr;
};

std::string getValue(std::string message, std::string defaultVal);


