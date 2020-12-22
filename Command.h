#ifndef MILESTONE1_COMMAND_H
#define MILESTONE1_COMMAND_H

#include "thread"
#include "string"
#include "vector"

using namespace std;

class Command {
public:
    virtual void execute(vector<string> v) = 0;
};

#endif //MILESTONE1_COMMAND_H
