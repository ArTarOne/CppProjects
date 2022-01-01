#include "ConsoleInterface.h"
#include "StdPlus/StdPlus.h"
#include "Application/ISettings.h"


ConsoleInterface::ConsoleInterface()
{
    
}

ConsoleInterface::~ConsoleInterface()
{

}

void ConsoleInterface::setFuncs(const FuncInfoContainer & funcs)
{
    resetFuncs();
    m_funcs = &funcs;
}

void ConsoleInterface::resetFuncs()
{
    m_funcs = nullptr;
}

void ConsoleInterface::setCommands(Commands & commands)
{
    m_ptrCommands = &commands;
}

void ConsoleInterface::resetCommands()
{
    m_ptrCommands = nullptr;
}

void ConsoleInterface::show()
 {
    std::string strPath = getValue("Enter path", m_settings->get("path"));
    m_settings->set("path", strPath);

    std::string strFolderMask = getValue("Enter folder mask", m_settings->get("folderMask"));
    m_settings->set("folderMask", strFolderMask);

    std::string strFileMask = getValue("Enter file mask", m_settings->get("fileMask"));
    m_settings->set("fileMask", strFileMask);
    
    executeCommand(e_idCommand_updateCore, *m_ptrCommands, m_settings);
    executeCommand(e_idCommand_startParseCommand, *m_ptrCommands);
    executeCommand(e_idCommand_saveSettings, *m_ptrCommands, m_settings);

    FuncInfoContainer allFuncs = *m_funcs;
    std::sort(allFuncs.begin(), allFuncs.end(), 
        [](const FuncInfo & left, const FuncInfo & right)
    {
        return left.funcSize() < right.funcSize();
    });

    for (const auto & funcInfo : allFuncs)
    {
        AMSG(funcInfo);
    }
    ASPLIT;
    AVAR(m_funcs->size());        
}

void ConsoleInterface::setSettings(ISettings * settings)
{
    m_settings = settings;
}

std::string getValue(std::string message, std::string defaultVal)
{   
    std::string value;
    std::cout << message << "[" << defaultVal << "]: ";
    getline(std::cin, value);

    if (value.empty())
        return defaultVal;

    return value;
}