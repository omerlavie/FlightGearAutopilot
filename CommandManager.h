#ifndef MILESTONE1_COMMANDMANAGER_H
#define MILESTONE1_COMMANDMANAGER_H

#include "VarCollection.h"
#include "Lexer.h"
#include "Command.h"

class CommandManager {
protected:
    // command map.
    map<string, Command*> cmdMap;
    // variable collection.
    VarCollection* varCollection;

public:
    Command* getCommand(vector<string> v);
    Command* getVarCommand(vector<string> v);
    Command* getConditionCommand(vector<string> conditionBlock);
};


#endif //MILESTONE1_COMMANDMANAGER_H
