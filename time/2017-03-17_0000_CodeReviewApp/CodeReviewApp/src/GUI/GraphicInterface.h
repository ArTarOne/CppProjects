#pragma once

#include "Application/IUserInterface.h"
#include "MainWindow.h"
#include "OptionsWindow.h"
#include "AboutWindow.h"
class GraphicInterface : public IUserInterface
{
    friend MainWindow;
    friend OptionsWindow;

public:
    GraphicInterface();

    ~GraphicInterface();

    virtual void setFuncs(const FuncInfoContainer & funcs) override;
    virtual void resetFuncs() override;
    virtual void setCommands(Commands & commands) override;
    virtual void resetCommands() override;
    virtual void show() override;


   

    virtual void setSettings(ISettings * settings) override;

private:
    MainWindow *              m_mainWindow   = nullptr;
    Commands *                m_ptrCommands  = nullptr;
    const FuncInfoContainer * m_funcs        = nullptr;
    OptionsWindow *           m_optionWindow = nullptr;
    ISettings *               m_settings     = nullptr;
    AboutWindow *             m_aboutWindow  = nullptr;

};

