#include "StdPlus/StdPlus.h"
#include "Commands.h"
#include "IUserInterface.h"

SetPathCommand::SetPathCommand(CodeReviewCore & core) 
	: m_core(core)
{

}

void SetPathCommand::execute(void * data /*= nullptr*/)
{
    std::string path = *static_cast<std::string *>(data);
	m_core.setPath(path);
}

IdCommand SetPathCommand::id() const
{
    return e_idCommand_setPathCommmand;
}

//////////////////////////////////////////////////////////////////////////
StartParseCommand::StartParseCommand(CodeReviewCore & core,
    IUserInterface * userInterface, FuncInfoContainer & foundFuncs)
    : m_core(core)
    , m_foundFuncs(foundFuncs)
    , m_userInterface(userInterface)
{

}

void StartParseCommand::execute(void * data )
{   
    try
    {   
        m_foundFuncs.clear();

        std::string tmpFolderMask = m_core.folderMask();
        std::string tmpFileMask = m_core.fileMask();

        std::vector<std::string> folderMasks = stdplus::split(m_core.folderMask(), ';');
        std::vector<std::string> fileMasks   = stdplus::split(m_core.fileMask(),   ';');
        
        for(std::string & folderMask : folderMasks)
        {
            folderMask = stdplus::trim(folderMask);
            m_core.setFolderMask(folderMask);

            for(std::string & fileMask : fileMasks)
            {
                fileMask = stdplus::trim(fileMask);
                m_core.setFileMask(fileMask);
                m_core.parse();
                FuncInfoContainer tmp = m_core.functions();
                m_foundFuncs.insert(m_foundFuncs.end(), tmp.begin(), tmp.end());
            }
        }
        m_userInterface->setFuncs(m_foundFuncs);

        m_core.setFolderMask(tmpFolderMask);
        m_core.setFileMask(tmpFileMask);
    }
    catch (std::logic_error & exeptInParseCore)
    {
        AVAR(exeptInParseCore.what());
    }    
}

IdCommand StartParseCommand::id() const
{
    return e_idCommand_startParseCommand;
}


//////////////////////////////////////////////////////////////////////////

UpdateCore::UpdateCore(CodeReviewCore & core)
    : m_core(core)
{

}

void UpdateCore::execute(void * inputOptions /*= nullptr*/)
{
    ISettings * options = static_cast<ISettings *>(inputOptions);
    
    m_core.setPath(options->get("path", "D:/"));
    m_core.setFolderMask(options->get("folderMask", "*"));
    m_core.setFileMask(options->get("fileMask", "*.cpp"));
    options->get("warningFuncSize", "30");  // TODO warning place in programm!
//    m_core.setWarningFuncSize(stdplus::to_int(options->get("warningFuncSize")));
}

IdCommand UpdateCore::id() const
{
    return e_idCommand_updateCore;
}

//////////////////////////////////////////////////////////////////////////

SaveSettings::SaveSettings(ISettings * settings)
    :m_settings(settings)
{

}

void SaveSettings::execute(void * data /*= nullptr*/)
{
    m_settings->save();
}

IdCommand SaveSettings::id() const
{
    return e_idCommand_saveSettings;
}
