#ifndef MILESTONE1_WHILECOMMAND_H
#define MILESTONE1_WHILECOMMAND_H

#include "Command.h"
#include "Parser.h"
#include "Calculator.h"

class WhileCommand : public Command, CommandManager {
public:
    WhileCommand(VarCollection* vc);
    void execute(vector<string> conditionBlock);
    bool isConditionTrue(vector<string> condition);
    void setCommandMap(map<string, Command*> cm);
};

#endif //MILESTONE1_WHILECOMMAND_H
