#include "SetValueCommand.h"

/****************************************************
 * Function Name:       SetValueCommand
 * The Input:           map<string, Command*> cm, VarCollection* vc
 * The Output:          null
 * Function Operation:  SetValueCommand constructor
 ****************************************************/
SetValueCommand::SetValueCommand(map<string, Command*> cm, VarCollection* vc) {
    this->cmdMap = cm;
    this->varCollection = vc;
}

/****************************************************
 * Function Name:       execute
 * The Input:           vector<string> v
 * The Output:
 * Function Operation:  The function extract the parameters from the line of command for parameters and execute the
 *                      set value command
 ****************************************************/
void SetValueCommand::execute(vector<string> v) {
    ConnectToServerCommand* ctsc = (ConnectToServerCommand*) cmdMap["connect"];
    DataWriterServer* d = ctsc->getServer();
    this->dws = d;
    string varName = v[0];
    vector<string> newv;
    //We push all the parameters into a vector (starting from index 2 to delete the decleration of the command in the code)
    for (int i = 2; i < v.size(); i++) {
        newv.push_back(v[i]);
    }
    string expString = Lexer::fromVectorToString(newv);
    double value = Calculator::calculateExpression(expString, this->varCollection);
    string path = findPath(varName);
    //If there is no path the the var we only update the value in value list.
    if (path == "") {
        changeValueInList(varName, value);
    } else {
        changeValueInSimulator(path, value);
    }
}

/****************************************************
 * Function Name:       findPath
 * The Input:           string varName
 * The Output:          the path of a given variable
 * Function Operation:  The functions iterates over the varMap and searched for a variable's name path.
 ****************************************************/
string SetValueCommand::findPath(string varName) {
    map<string, pair<string, double>> varMap = this->varCollection->getVariablesMap();
    for (auto var : varMap) {
        if (var.first == varName) {
            return var.second.first;
        }
    }
    throw("Unknown variable name '" + varName + "'.");
}

/****************************************************
 * Function Name:       changeValueInList
 * The Input:           string varName, double value
 * The Output:          null
 * Function Operation:  The functions changes a value of a variable in the varCollection member.
 ****************************************************/
void SetValueCommand::changeValueInList(string varName, double value) {
    this->varCollection->updateValue(varName, value);
}

/****************************************************
 * Function Name:       changeValueInSimulator
 * The Input:           string varName, double value
 * The Output:          null
 * Function Operation:  The functions changes a value of a variable in the flight simulator.
 ****************************************************/
void SetValueCommand::changeValueInSimulator(string path, double value) {
    //Creating the message to send for the server.
    string s = "set " + path + " " + to_string(value);
    char* message = new char[s.length() + 3];
    strcpy(message, s.c_str());
    strcat(message, "\r\n");
    //Sending the message.
    this->dws->writeToServer(message);
    delete[](message);
}
