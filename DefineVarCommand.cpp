#include "DefineVarCommand.h"

/****************************************************
 * Function Name:       DefineVarCommand
 * The Input:           VarCollection* vc
 * The Output:          null
 * Function Operation:  DefineVarCommand constructor
 ****************************************************/
DefineVarCommand::DefineVarCommand(VarCollection* vc) {
    this->vCollection = vc;
}

/****************************************************
 * Function Name:       execute
 * The Input:           vector<string> v:
 * The Output:
 * Function Operation:  The function extract the parameters from the line and add the var to vCollection.
 ****************************************************/
void DefineVarCommand::execute(vector<string> v) {
    string name = v[1];
    string path = "";
    // check if the variable is bound to a direct path. else, it is bound to another variable.
    if (v[3].at(0) == '"') {
        // remove the " "
        int len = v[3].length();
        path = v[3].substr(1, len - 2);
    } else {
        // find the binded variable's path.
        path = this->vCollection->getVariablesMap()[v[3]].first;
    }
    // add the new variable to the list.
    this->vCollection->addVar(name, path, 0);
}

