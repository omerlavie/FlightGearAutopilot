#ifndef MILESTONE1_DEFINEVARCOMMAND_H
#define MILESTONE1_DEFINEVARCOMMAND_H

#include "Command.h"
#include "VarCollection.h"

class DefineVarCommand : public Command {
private:
    // variable collection.
    VarCollection* vCollection;

public:
    DefineVarCommand(VarCollection* vc);
    void execute(vector<string> v);
};

#endif //MILESTONE1_DEFINEVARCOMMAND_H
