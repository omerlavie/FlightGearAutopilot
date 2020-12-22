#ifndef MILESTONE1_CONNECTTOSERVERCOMMAND_H
#define MILESTONE1_CONNECTTOSERVERCOMMAND_H

#include "Command.h"
#include "DataWriterServer.h"
#include "Lexer.h"
#include "Calculator.h"

class ConnectToServerCommand : public Command {
private:
    // client server.
    DataWriterServer* dws;
    // variable collection.
    VarCollection* varCollection;

public:
    ConnectToServerCommand(VarCollection* vc);
    DataWriterServer* getServer();
    void execute(vector<string> v);
    ~ConnectToServerCommand();
};

#endif //MILESTONE1_CONNECTTOSERVERCOMMAND_H
