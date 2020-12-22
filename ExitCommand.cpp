#include "ExitCommand.h"

/****************************************************
 * Function Name:       ExitCommand
 * The Input:           VarCollection *vc, map<string, Command *> cm
 * The Output:          nullptr
 * Function Operation:  ExitCommand command.
 ****************************************************/
ExitCommand::ExitCommand(VarCollection* vc) {
    this->varCollection = vc;
}

/****************************************************
 * Function Name:       execute
 * The Input:           VarCollection *vc, map<string, Command *> cm
 * The Output:
 * Function Operation:  The function calls shut down function of both write and read servers.
 *                      shut down closes the sockets and stop the while loop (if exists) so the thread can be joined.
 ****************************************************/
void ExitCommand::execute(vector<string> v) {
    ((OpenServerCommand*)this->cmdMap["openDataServer"])->getServer()->shutDown();
    ((ConnectToServerCommand*)this->cmdMap["connect"])->getServer()->shutDown();
}

/****************************************************
 * Function Name:       setCommandMap
 * The Input:           map<string, Command *> cm
 * The Output:          null
 * Function Operation:  sets cm as cmdMap member.
 ****************************************************/
void ExitCommand::setCommandMap(map<string, Command *> cm) {
    this->cmdMap = cm;
}

/****************************************************
 * Function Name:       destructor.
 * The Input:
 * The Output:
 * Function Operation:  deletes all the commands and the var collection.
 ****************************************************/
ExitCommand::~ExitCommand() {
    delete((OpenServerCommand*) this->cmdMap["openDataServer"]);
    delete((ConnectToServerCommand*) this->cmdMap["connect"]);
    delete((DefineVarCommand*) this->cmdMap["defineVar"]);
    delete((AssignVarCommand*) this->cmdMap["assignVar"]);
    delete((SetValueCommand*) this->cmdMap["setValue"]);
    delete((SleepCommand*) this->cmdMap["sleep"]);
    delete((PrintCommand*) this->cmdMap["print"]);
    delete((IfCommand*) this->cmdMap["if"]);
    delete((WhileCommand*) this->cmdMap["while"]);
    delete(this->varCollection);
}