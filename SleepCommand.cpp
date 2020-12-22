#include "SleepCommand.h"

/****************************************************
 * Function Name:       constructor.
 * The Input:           VarCollection* vc.
 * The Output:
 * Function Operation:  constructs a sleep command object.
 ****************************************************/
SleepCommand::SleepCommand(VarCollection* vc) {
    this->varCollection = vc;
}

/****************************************************
 * Function Name:       execute
 * The Input:           vector<string> v
 * The Output:
 * Function Operation:  The function execute the sleep command in milliseconds
 ****************************************************/
void SleepCommand::execute(vector<string> v) {
    string s = "";
    for (int i = 1; i < v.size(); i++) {
        s += v[i];
    }
    //Adjusting the sleep time to milliseconds.
    double sleepInSeconds = Calculator::calculateExpression(s, this->varCollection) / 1000;
    sleep(sleepInSeconds);
}