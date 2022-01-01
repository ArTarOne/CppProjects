#pragma once

#include "StdPlus/StdInclude.h"

enum IdCommand
{
    e_idCommand_setPathCommmand,
    e_idCommand_startParseCommand,
    e_idCommand_updateCore,
    e_idCommand_saveSettings,
};

class ICommand
{
public:
    virtual IdCommand id() const = 0;
	virtual void execute(void * data = nullptr) = 0;
    virtual ~ICommand() {}

    inline bool operator<(const ICommand & other)
    {
        return this->id() < other.id();
    }
};

inline std::ostream & operator<<(std::ostream & os, const ICommand * cmd)
{
    os << cmd->id();
    return os;
}

typedef std::vector<ICommand *> Commands;

inline ICommand * getCommand(IdCommand id, Commands & commands)
{
    auto it = std::find_if(commands.begin(), commands.end(),
        [&id](const ICommand * cmd)
    {
        if (cmd->id() == id)
            return true;

        return false;
    });

    if (it != commands.end())
        return *it;

    throw std::logic_error("not found command");
}

inline void executeCommand(IdCommand id, Commands & commands, void * data = nullptr)
{
    getCommand(id, commands)->execute(data);
}