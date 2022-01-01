#pragma once

#include "ExportCodeReviewApplication.h"
#include "Core/CodeReviewCore.h"
#include "StdPlus/StdPlus.h"
#include "ICommand.h"

class ISettings;
class IUserInterface;

class CODE_REVIEW_APPLICATION_API Application 
{
public:
	Application(int argc, char *argv[]);
    virtual ~Application();

    void setISettings(ISettings * settings);
    void setIUserInterface(IUserInterface * userInterface);
    void start();

private:
    void initCommands();
    
	CodeReviewCore    m_core;
    ISettings *       m_settings      = nullptr;
	IUserInterface *  m_userInterface = nullptr;	
    Commands          m_commands;
    FuncInfoContainer m_foundFuncs;  
    
};