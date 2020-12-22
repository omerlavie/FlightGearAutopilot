#ifndef MILESTONE1_ASSIGNVARCOMMAND_H
#define MILESTONE1_ASSIGNVARCOMMAND_H

#include "Parser.h"
#include "Calculator.h"

class AssignVarCommand : public Command {
private:
    // variable collection.
    VarCollection* vCollection;
public:
    AssignVarCommand(VarCollection* vc);
    void execute(vector<string> v);
};


#endif //MILESTONE1_ASSIGNVARCOMMAND_H
