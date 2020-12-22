#include "OpenServerCommand.h"

/****************************************************
 * Function Name:       OpenServerCommand
 * The Input:           VarCollection* vc
 * The Output:          null
 * Function Operation:  OpenServerCommand constructor
 ****************************************************/
OpenServerCommand::OpenServerCommand(VarCollection* vc) {
    this->varsCollection = vc;
}

/****************************************************
 * Function Name:       execute
 * The Input:           vector<string> v
 * The Output:
 * Function Operation:  The function extract the text from v and open a thread with openServer and the port, and herz as
 *                      parameters
 ****************************************************/
void OpenServerCommand::execute(vector<string> v) {
    vector<string> newv = {};
    for (int i = 1; i < v.size(); i++) {
        newv.push_back(v[i]);
    }
    vector<string> finalv = Lexer::arrangeOpenServerExpression(newv);
    int port = (int) Calculator::calculateExpression(finalv[0], this->varsCollection);
    int herz = (int) Calculator::calculateExpression(finalv[1], this->varsCollection);
    // create DataReaderServer object.
    this->drs = new DataReaderServer(port, herz);
    // open the server and wait for the buffer to load first information from server.
    this->drs->openServer(this->varsCollection);
    // start running the reading function in a new thread.
    this->t = new thread(&DataReaderServer::readFromServer, this->drs, this->varsCollection);
    // wait for the user to approve that he managed to open the simulator and autostart (if meant to).
    this->enterc();
}

/****************************************************
 * Function Name:       enterc
 * The Input:
 * The Output:
 * Function Operation:  after the data reader thread has started running, the main thread will wait for the user to
 *                      enter a char before procceeding to parse the next line (so the user has enough time to open
 *                      the simulator and autostart the plane).
 ****************************************************/
void OpenServerCommand::enterc() {
    char ch;
    cout << "Enter any key to continue." << endl;
    scanf("%c", &ch);
}

/****************************************************
 * Function Name:       getServer
 * The Input:           null
 * The Output:          this->drs
 * Function Operation:  The function returns drs member
 ****************************************************/
DataReaderServer* OpenServerCommand::getServer() {
    return this->drs;
}

/****************************************************
 * Function Name:       destructor.
 * The Input:           null
 * The Output:          null
 * Function Operation:  OpenServerCommand destructor
 ****************************************************/
OpenServerCommand::~OpenServerCommand() {
    // join the thread.
    this->t->join();
    // delete thread object and data reader server.
    delete(this->t);
    delete(this->drs);
};