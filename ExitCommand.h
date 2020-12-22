#ifndef MILESTONE1_EXITCOMMAND_H
#define MILESTONE1_EXITCOMMAND_H

#include "Command.h"
#include "VarCollection.h"
#include "CommandManager.h"
#include "OpenServerCommand.h"
#include "ConnectToServerCommand.h"
#include "DefineVarCommand.h"
#include "AssignVarCommand.h"
#include "SetValueCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"

class ExitCommand : public Command {
private:
    // variable collection.
    VarCollection* varCollection;
    // command map.
    map<string, Command*> cmdMap;

public:
    ExitCommand(VarCollection* vc);
    void execute(vector<string> v);
    void setCommandMap(map<string, Command*> cm);
    ~ExitCommand();
};

#endif //MILESTONE1_EXITCOMMAND_H
