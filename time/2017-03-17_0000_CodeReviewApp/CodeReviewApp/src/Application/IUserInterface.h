#pragma once

#include "StdPlus/StdInclude.h"
#include "Core/FuncInfo.h"
#include "ICommand.h"
#include "ISettings.h"

class IUserInterface
{
public:
    void operator=(const IUserInterface &) = delete;
    virtual ~IUserInterface() {}

	virtual void setFuncs(const FuncInfoContainer & funcs) = 0;
	virtual void resetFuncs() = 0;

	virtual void setCommands(Commands & commands) = 0;
	virtual void resetCommands() = 0; 

    virtual void setSettings(ISettings * settings) = 0;

    virtual void show() = 0;
};