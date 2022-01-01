#include "GraphicInterface.h"
#include "StdPlus/StdPlus.h"
#include "Application/ISettings.h"


GraphicInterface::GraphicInterface()
{

}

GraphicInterface::~GraphicInterface()
{
    delete m_mainWindow;
}

void GraphicInterface::setFuncs(const FuncInfoContainer & funcs)
{
    resetFuncs();
    m_funcs = &funcs;
    m_mainWindow->makeTableWidgetForFuncInfo(funcs);
}

void GraphicInterface::resetFuncs()
{
    m_funcs = nullptr;
}

void GraphicInterface::setCommands(Commands & commands)
{
    m_ptrCommands = &commands;
}

void GraphicInterface::resetCommands()
{
    m_ptrCommands = nullptr;
}

void GraphicInterface::show()
{
    m_mainWindow = new MainWindow();
    m_mainWindow->setGraphicInterface(this);
    m_mainWindow->show(); 

    m_optionWindow = new OptionsWindow();
    m_optionWindow->setGraphicInterface(this);

    m_aboutWindow = new AboutWindow();
    m_aboutWindow->setGraphicInterface(this);


    QObject::connect(m_mainWindow->ui.actionOptions,
        SIGNAL(triggered()), m_optionWindow, SLOT(show()));

    QObject::connect(m_optionWindow->uiOptions.bCansel,
        SIGNAL(clicked()), m_optionWindow, SLOT(hide()));

    QObject::connect(m_optionWindow->uiOptions.bSave,
        SIGNAL(clicked()), m_optionWindow, SLOT(onButtonSave()));

    QObject::connect(m_mainWindow->ui.actionAbout,
        SIGNAL(triggered()), m_aboutWindow, SLOT(show()));

}



void GraphicInterface::setSettings(ISettings * settings)
{
    m_settings =  settings;
}

