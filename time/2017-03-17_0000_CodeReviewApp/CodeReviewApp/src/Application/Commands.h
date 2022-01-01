#pragma once

#include "ICommand.h"
#include "Core/CodeReviewCore.h"
#include "ISettings.h"


class IUserInterface;

class SetPathCommand : public ICommand
{
public:
	SetPathCommand(CodeReviewCore & core);

	virtual void execute(void * data = nullptr) override;

    virtual IdCommand id() const override;

private:
	CodeReviewCore & m_core;
};


class StartParseCommand : public ICommand
{
public:
    StartParseCommand(CodeReviewCore & core, 
        IUserInterface * userInterface, FuncInfoContainer & foundFuncs);
    
    virtual void execute(void * data = nullptr) override;

    virtual IdCommand id() const override;

private:
    CodeReviewCore &    m_core;
    IUserInterface *     m_userInterface = nullptr;
    FuncInfoContainer & m_foundFuncs;
};

class UpdateCore : public ICommand
{
public:
    UpdateCore(CodeReviewCore & core);

    virtual void execute(void * data = nullptr) override;

    virtual IdCommand id() const override;

private:
    CodeReviewCore & m_core;
};


class SaveSettings : public ICommand
{
public:
    SaveSettings(ISettings * settings);

    virtual void execute(void * data = nullptr) override;

    virtual IdCommand id() const override;

private:
    ISettings * m_settings;
};