#ifndef MILESTONE1_PRINTCOMMAND_H
#define MILESTONE1_PRINTCOMMAND_H

#include "Command.h"
#include "Lexer.h"
#include "VarCollection.h"

class PrintCommand : public Command {
private:
    // variable collection.
    VarCollection* varCollection;

public:
    PrintCommand(VarCollection* varCollection);
    void execute(vector<string> v);
};


#endif //MILESTONE1_PRINTCOMMAND_H
