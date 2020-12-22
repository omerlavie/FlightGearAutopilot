#ifndef MILESTONE1_IFCOMMAND_H
#define MILESTONE1_IFCOMMAND_H

#include "Command.h"
#include "Parser.h"
#include "Calculator.h"

class IfCommand : public Command, CommandManager {
public:
    IfCommand(VarCollection* vc);
    void execute(vector<string> conditionBlock);
    bool isConditionTrue(vector<string> condition);
    void setCommandMap(map<string, Command*> cm);
};

#endif //MILESTONE1_IFCOMMAND_H
