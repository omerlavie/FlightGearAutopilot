#include "ConnectToServerCommand.h"

/****************************************************
 * Function Name:       constructor.
 * The Input:           VarCollection* vc.
 * The Output:
 * Function Operation:  constructs a connect to server command object.
 ****************************************************/
ConnectToServerCommand::ConnectToServerCommand(VarCollection* vc) {
    this->varCollection = vc;
}
/****************************************************
 * Function Name:       execute
 * The Input:           vector<string> v: the parameters to execute the connect to server command
 * The Output:
 * Function Operation:  The function extract the parameters from the lines and send it to DataWriterServer constructor
 ****************************************************/
void ConnectToServerCommand::execute(vector<string> v) {
    char* host = Lexer::stringToCharPtr(v[1]);
    string s = "";
    for (int i = 2; i < v.size(); i++) {
        s += v[i];
    }
    int port = (int) Calculator::calculateExpression(s, this->varCollection);
    this->dws = new DataWriterServer(host, port);
    this->dws->connectToServer();
}

/****************************************************
 * Function Name:       getServer
 * The Input:           null
 * The Output:          his->dws
 * Function Operation:  The functions returns the dws member
 ****************************************************/
DataWriterServer* ConnectToServerCommand::getServer() {
    return this->dws;
}


/****************************************************
 * Function Name:       ~ConnectToServerCommand
 * The Input:           null
 * The Output:          null
 * Function Operation:  ConnectToServerCommand destructor
 ****************************************************/
ConnectToServerCommand::~ConnectToServerCommand() {
    delete(this->dws);
};
