#include "PrintCommand.h"

/****************************************************
 * Function Name:       PrintCommand
 * The Input:           VarCollection* vc
 * The Output:          null
 * Function Operation:  PrintCommand constructor
 ****************************************************/
PrintCommand::PrintCommand(VarCollection* vc) {
    this->varCollection = vc;
}

/****************************************************
 * Function Name:       execute
 * The Input:           vector<string> v
 * The Output:
 * Function Operation:  The function extract the parameters from the line of command for parameters and execute the
 *                      print command.
 ****************************************************/
void PrintCommand::execute(vector<string> v) {
    vector<string> newv = {};
    // add all of the elements but "print" to a new vector.
    for (int i = 1; i < v.size(); i++) {
        newv.push_back(v[i]);
    }
    string s = Lexer::fromVectorToStringWithSpaces(newv);
    map<string, pair<string, double>> varMap = this->varCollection->getVariablesMap();
    // check if the string is a key in the var map.
    if (Lexer::keyExist(s, varMap)) {
        // if it is, find the key and print it's value.
        for (auto var : varMap) {
            if (var.first == s) {
                cout << var.second.second << endl;
            }
        }
    }
    else {
        // if it's not a variable it is a string. remove quotation marks and print it.
        string noQMarks = "";
        for (int i = 1; i < s.size() - 1; i++) {
            noQMarks += s.at(i);
        }
        cout << noQMarks << endl;
    }
}


