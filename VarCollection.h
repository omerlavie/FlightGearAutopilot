#ifndef MILESTONE1_VARCOLLECTION_H
#define MILESTONE1_VARCOLLECTION_H

#include <vector>
#include "map"
#include "string"
#include "Expression.h"

using namespace std;

class VarCollection {
private:
    // mapping var name to pairs of path and value.
    map<string, pair<string, double>> symbolTable;
    // expressions to delete.
    vector<Expression*> expressionsForDestruction;

public:
    VarCollection();
    void addVar(string name, string path, double value);
    void updateValue(string name, double value);
    map<string, pair<string, double>> getVariablesMap();
    void addToDestructionList(Expression* e);
    ~VarCollection();
};

#endif //MILESTONE1_VARCOLLECTION_H
