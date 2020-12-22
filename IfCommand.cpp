#include "IfCommand.h"

/****************************************************
 * Function Name:       constructor of if command.
 * The Input:           command map, var collection.
 * The Output:
 * Function Operation:  constructs a if command.
 ****************************************************/
IfCommand::IfCommand(VarCollection* vc) {
    this->varCollection = vc;
}

/****************************************************
 * Function Name:       isConditionTrue
 * The Input:           vector<string> condition - a splitted line of condition.
 * The Output:          boolean value of the condition.
 * Function Operation:  separates expression 1, expression 2, and comparator. calculates both expressions and
 *                      compares them by the comparator type.
 ****************************************************/
bool IfCommand::isConditionTrue(vector<string> condition) {
    vector<string> newv = {};
    // move all strings but "while" to a new vector.
    for (int i = 1; i < condition.size(); i++) {
        newv.push_back(condition[i]);
    }
    vector<string> separatedCondition = Lexer::separateCondition(newv);
    // separate expression1, expression2, comparator.
    string comparator = separatedCondition[1];
    string ex1String = separatedCondition[0];
    string ex2String = separatedCondition[2];
    // calculate both expressions.
    double result1 = Calculator::calculateExpression(ex1String, this->varCollection);
    double result2 = Calculator::calculateExpression(ex2String, this->varCollection);
    // return true/false by the comparison both results.
    if (comparator == "==") {
        return result1 == result2;
    }
    if (comparator == "!=") {
        return result1 != result2;
    }
    if (comparator == "<=") {
        return result1 <= result2;
    }
    if (comparator == ">=") {
        return result1 >= result2;
    }
    if (comparator == ">") {
        return result1 > result2;
    }
    if (comparator == "<") {
        return result1 < result2;
    }
}

/****************************************************
 * Function Name:       execute.
 * The Input:           vector<string> linesVector - each line of the condition block is a string in the vector.
 * The Output:
 * Function Operation:  first checks if the closing scope is in separate line, if not - removes it, if it is - it takes
 *                      out last line, and then iterates the lines of the block and executes each command
 *                      (if condition is true).
 ****************************************************/
void IfCommand::execute(vector<string> linesVector) {
    // check if the closing scope appears in a separate line or it is appended to last line.
    int beginning = 0, end = 0;
    string conditionLine = linesVector[0];
    vector<string> conditionVector = Lexer::fromLineToVectorOfStrings(conditionLine);
    if (linesVector[1] != "{") {
        beginning = 1;
    } else {
        beginning = 2;
    }
    // if the last line of block equals to "}", it is not a relevant line and we will skip on parsing it.
    if (linesVector[linesVector.size() - 1] == "}") {
        end = linesVector.size() - 1;
    } else {
        end = linesVector.size();
    }
    // if the condition is true, iterate the relevant lines.
    if (isConditionTrue(conditionVector)) {
        for (int i = beginning; i < end; i++) {
            Command *cmd;
            string currentLine = linesVector[i];
            vector<string> splittedLine = Lexer::fromLineToVectorOfStrings(currentLine);
            // if the splitted line begins with if/while, it is treated as a condition line and the next lines as
            // condition block.
            if ((splittedLine[0] == "if") || (splittedLine[0] == "while")) {
                vector<string> conditionBlock = Lexer::returnConditionBlock(linesVector, i);
                i += conditionBlock.size() - 1;
                cmd = this->getConditionCommand(conditionBlock);
                cmd->execute(conditionBlock);
                // else - it is treated as a regular command and execute it.
            } else {
                vector<string> splittedLineNoScopes = Lexer::removeScopesFromVector(splittedLine);
                cmd = this->getCommand(splittedLineNoScopes);
                cmd->execute(splittedLineNoScopes);
            }
        }
    }
}

/****************************************************
 * Function Name:       setCommandMap.
 * The Input:           map<string, Command *> cm
 * The Output:          null
 * Function Operation:  sets the cm as a member.
 ****************************************************/
void IfCommand::setCommandMap(map<string, Command *> cm) {
    this->cmdMap = cm;
}