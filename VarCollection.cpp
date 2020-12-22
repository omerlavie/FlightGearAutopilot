#include <iostream>
#include <mutex>
#include "VarCollection.h"

/****************************************************
 * Function Name:       VarCollection.
 * The Input:           null
 * The Output:          null
 * Function Operation:  VarCollection constructor.
 ****************************************************/
VarCollection::VarCollection() {
    this->symbolTable = {};
    this->expressionsForDestruction = {};
}

/****************************************************
 * Function Name:       addVar.
 * The Input:           string name, string path, double value.
 * The Output:          null
 * Function Operation:  The function add a variable to the collection by it's name, path and value.
 ****************************************************/
void VarCollection::addVar(string name, string path, double value) {
    pair<string, double> p;
    p.first = path;
    p.second = value;
    this->symbolTable[name] = p;
}

/****************************************************
 * Function Name:       getVariablesMap.
 * The Input:           null
 * The Output:          this->symbolTable
 * Function Operation:  The function resturns the symbolTable member.
 ****************************************************/
map<string, pair<string, double>> VarCollection::getVariablesMap() {
    return this->symbolTable;
}

/****************************************************
 * Function Name:       updateValue.
 * The Input:           string name, double value
 * The Output:          null
 * Function Operation:  The function updates variable's value.
 ****************************************************/
void VarCollection::updateValue(string name, double value) {
    this->symbolTable[name].second = value;
}

/****************************************************
 * Function Name:       addToDestructionList.
 * The Input:           Expression* e : an expression that was created for calculating a value and is no longer needed.
 * The Output:
 * Function Operation:  The function adds unnecessary expression into a new list so we can delete them at the end.
 ****************************************************/
void VarCollection::addToDestructionList(Expression* e) {
    this->expressionsForDestruction.push_back(e);
}

/****************************************************
 * Function Name:       destructor.
 * The Input:
 * The Output:
 * Function Operation:  deletes all the expressions that have been in use during runtime.
 ****************************************************/
VarCollection::~VarCollection(){
    for (int i = 0; i < this->expressionsForDestruction.size(); i++) {
        delete(this->expressionsForDestruction[i]);
    }
}