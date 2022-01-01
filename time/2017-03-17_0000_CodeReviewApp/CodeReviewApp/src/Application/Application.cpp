#include "Application.h"

#include "StdPlus/StdPlus.h"
#include "Commands.h"
#include "ISettings.h"
#include "IUserInterface.h"


Application::Application(int argc, char *argv[])
{

}

Application::~Application()
{

}

void Application::start()
{
    if (m_settings == nullptr)
        throw std::logic_error("Don't setup settings for Application");

    if (m_userInterface == nullptr)
        throw std::logic_error("Don't setup UserInterface for Application");

    m_userInterface->setSettings(m_settings);

    initCommands();    

    executeCommand(e_idCommand_updateCore, m_commands, m_settings);

    m_userInterface->show();
}

void Application::setISettings(ISettings * settings)
{
    m_settings = settings;
}

void Application::setIUserInterface(IUserInterface * userInterface)
{
    m_userInterface = userInterface;
}

void Application::initCommands()
{
    m_commands = 
    {
        new SetPathCommand(m_core),
        new StartParseCommand(m_core, m_userInterface, m_foundFuncs),
        new UpdateCore(m_core),
        new SaveSettings(m_settings),
    };
    
    m_userInterface->setCommands(m_commands);
}
