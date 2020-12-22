#include "AssignVarCommand.h"

/****************************************************
 * Function Name:       constructor.
 * The Input:           VarCollection* vc: variable collection.
 * The Output:          null
 * Function Operation:  constructs an assign var command.
 ****************************************************/
AssignVarCommand::AssignVarCommand(VarCollection* vc) {
    this->vCollection = vc;
}

/****************************************************
 * Function Name:       execute.
 * The Input:           vector<string> v: a vector of the splitted command line.
 * The Output:
 * Function Operation:  adds a new variable with no path to the variable list.
 ****************************************************/
void AssignVarCommand::execute(vector<string> v) {
    // format of vector is : "var varname {splitted expression}"
    string name = v[1];
    string path = "";
    vector<string> newv = {};
    // create a new vector from 3rd element and on (skip "var varname" and add the expression parts).
    for (int i = 2; i < v.size(); i++) {
        newv.push_back(v[i]);
    }
    // turn the new vector into a string (which represents an expression).
    string expString = Lexer::fromVectorToString(newv);
    double result = Calculator::calculateExpression(expString, this->vCollection);
    // add as variable with value and with no path
    this->vCollection->addVar(name, path, result);
}