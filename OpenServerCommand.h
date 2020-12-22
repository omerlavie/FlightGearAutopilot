#ifndef MILESTONE1_OPENSERVERCOMMAND_H
#define MILESTONE1_OPENSERVERCOMMAND_H

#include "Command.h"
#include "Lexer.h"
#include "Calculator.h"
#include "DataReaderServer.h"
#include "VarCollection.h"

class OpenServerCommand : public Command {
private:
    // variable collection.
    VarCollection* varsCollection;
    // server.
    DataReaderServer* drs;
    // the thread that runs the data reading loop.
    thread* t;

public:
    OpenServerCommand(VarCollection* vc);
    void execute(vector<string> v);
    DataReaderServer* getServer();
    ~OpenServerCommand();
    void enterc();
};

#endif //MILESTONE1_OPENSERVERCOMMAND_H
