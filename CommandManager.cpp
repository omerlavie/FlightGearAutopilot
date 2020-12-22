#include "CommandManager.h"

/****************************************************
 * Function Name:       getCommand.
 * The Input:           vector of strings.
 * The Output:          command object.
 * Function Operation:  the function looks for the needed command in the command map and returns it
 *                      (based on the information given at the vector).
 ****************************************************/
Command* CommandManager::getCommand(vector<string> v) {
    // check if the first string is a variable's name.
    map<string, pair<string, double>> varMap = this->varCollection->getVariablesMap();
    for (auto var : varMap) {
        if (var.first == v[0]) {
            return this->cmdMap["setValue"];
        }
    }
    // in case the line begins with "var", there's more than one possible command.
    if (v[0] == "var") {
        return getVarCommand(v);
    }
    return this->cmdMap[v[0]];
}

/****************************************************
 * Function Name:       getVarCommand.
 * The Input:           vector<string> v: vector of strings.
 * The Output:          Command*: ptr to command object.
 * Function Operation:  the function receives a vector that begins with "var", decides which command needs to be
 *                      operated and returns it.
 ****************************************************/
Command* CommandManager::getVarCommand(vector<string> v) {
    // in case bind is the 3rd word, call defineVar command.
    if (v[2] == "bind") {
        return this->cmdMap["defineVar"];
        // if "bind" does not appear, call assign var which creates a new var with no path.
    } else {
        return this->cmdMap["assignVar"];
    }
}

/****************************************************
 * Function Name:       getConditionCommand.
 * The Input:           vector<string> conditionBlock: each line of the condition block is a string in the vector.
 * The Output:          Command*: a condition command object.
 * Function Operation:  decides which command object is needed (if / while) depends on the first string.
 ****************************************************/
Command* CommandManager::getConditionCommand(vector<string> conditionBlock){
    vector<string> firstLineV = Lexer::fromLineToVectorOfStrings(conditionBlock[0]);
    string conditionType = firstLineV[0];
    Command* cmd =  this->cmdMap[conditionType];
    return cmd;
}