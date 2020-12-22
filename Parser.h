#ifndef MILESTONE1_PARSER_H
#define MILESTONE1_PARSER_H

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
#include "ExitCommand.h"

class Parser : public CommandManager {
private:
    // path of text file.
    string path;

public:
    Parser(string p);
    void createCmdMap();
    void parse();
    ~Parser();
    };

#endif //MILESTONE1_PARSER_H
