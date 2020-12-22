#ifndef MILESTONE1_SLEEPCOMMAND_H
#define MILESTONE1_SLEEPCOMMAND_H

#include "Command.h"
#include "Lexer.h"
#include "Calculator.h"
#include <unistd.h>

class SleepCommand : public Command {
private:
    // variable collection.
    VarCollection* varCollection;

public:
    SleepCommand(VarCollection* vc);
    void execute(vector<string> v);

};


#endif //MILESTONE1_SLEEPCOMMAND_H
