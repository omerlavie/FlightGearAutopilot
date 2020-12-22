#ifndef MILESTONE1_SETVALUECOMMAND_H
#define MILESTONE1_SETVALUECOMMAND_H

#include "Command.h"
#include "Parser.h"
#include "Lexer.h"
#include "Calculator.h"
#include "VarCollection.h"
#include "DataWriterServer.h"

class SetValueCommand : public Command {
private:
    // client server.
    DataWriterServer* dws;
    // command map.
    map<string, Command*> cmdMap;
    // variable collection.
    VarCollection* varCollection;

public:
    SetValueCommand(map<string, Command*> cmdMap, VarCollection* vc);
    void execute(vector<string> v);
    double calculateExpression(vector<string> v);
    string findPath(string varName);
    void changeValueInList(string varName, double value);
    void changeValueInSimulator(string path, double value);
};

#endif //MILESTONE1_SETVALUECOMMAND_H