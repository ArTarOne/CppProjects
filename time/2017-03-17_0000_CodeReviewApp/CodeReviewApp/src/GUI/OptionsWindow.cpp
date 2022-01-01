#include "optionswindow.h"
#include "ui_optionswindow.h"
#include "GraphicInterface.h"
#include "StdPlus/StdPlus.h"

OptionsWindow::OptionsWindow(QWidget *parent) :
    QDialog(parent)
   
{
    uiOptions.setupUi(this);
   

}

OptionsWindow::~OptionsWindow()
{
   
}


void OptionsWindow::setGraphicInterface(GraphicInterface * graphicInterface)
{
    m_graphicInterface = graphicInterface;

    std::string folderMask = m_graphicInterface->m_settings->get("folderMask");
    std::string fileMask = m_graphicInterface->m_settings->get("fileMask");
    std::string workingSize = m_graphicInterface->m_settings->get("warningFuncSize");

    uiOptions.lineEdFolder->setText(QString::fromStdString(folderMask));
    uiOptions.lineEdFile->setText(QString::fromStdString(fileMask));
    uiOptions.lineEdSize->setText(QString::fromStdString(workingSize));
    
}

void OptionsWindow::onButtonSave()
{
    std::string strFolderMask = uiOptions.lineEdFolder->text().toStdString();
    std::string strFileMask = uiOptions.lineEdFile->text().toStdString();
    int sizeFunc = uiOptions.lineEdSize->text().toInt();
    


    m_graphicInterface->m_settings->set("folderMask",strFolderMask);
    m_graphicInterface->m_settings->set("fileMask",strFileMask);
    m_graphicInterface->m_settings->set("warningFuncSize", std::to_string(sizeFunc));


//     ICommand * cmdUpdateCore
//         = getCommand(e_idCommand_updateCore, *m_graphicInterface->m_ptrCommands);
//  
//     cmdUpdateCore->execute(m_graphicInterface->m_settings);

    executeCommand(e_idCommand_updateCore, 
        *m_graphicInterface->m_ptrCommands, m_graphicInterface->m_settings);

    hide();
}