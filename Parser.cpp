#include "Parser.h"

/****************************************************
 * Function Name:       Parser constructor.
 * The Input:
 * The Output:
 * Function Operation:  constructs a new parser object. the main purpose of the parse is to receive
 *                      a text line and parse it, find the necessary command and return it while organizing the
 *                      needed information parsed from the text.
 ****************************************************/
Parser::Parser(string p) {
    // create a var collection object to keep track of the variables added.
    this->varCollection = new VarCollection();
    this->cmdMap = {};
    this->path = p;
    createCmdMap();
}

/****************************************************
 * Function Name:       createCmdMap.
 * The Input:
 * The Output:
 * Function Operation:  create a map from string to command.
 *                      some commands use the var collection and some use the command map.
 *                      each command us created once, and when needed, execute function is called
 *                      with different parameters.
 ****************************************************/
void Parser::createCmdMap() {
    this->cmdMap["openDataServer"] = new OpenServerCommand(this->varCollection);
    this->cmdMap["connect"] = new ConnectToServerCommand(this->varCollection);
    this->cmdMap["defineVar"] = new DefineVarCommand(this->varCollection);
    this->cmdMap["assignVar"] = new AssignVarCommand(this->varCollection);
    this->cmdMap["setValue"] = new SetValueCommand(this->cmdMap, this->varCollection);
    this->cmdMap["sleep"] = new SleepCommand(this->varCollection);
    this->cmdMap["print"] = new PrintCommand(this->varCollection);
    IfCommand* ifc = new IfCommand(this->varCollection);
    this->cmdMap["if"] = ifc;
    WhileCommand* whilec = new WhileCommand(this->varCollection);
    this->cmdMap["while"] = whilec;
    ExitCommand* exitc = new ExitCommand(this->varCollection);
    this->cmdMap["exit"] = exitc;
    // for commands who need to "find" themselves in the cmdmap, set the whole map after creation.
    // (the map will not be passed to the constructor).
    ifc->setCommandMap(this->cmdMap);
    whilec->setCommandMap(this->cmdMap);
    exitc->setCommandMap(this->cmdMap);
}

/****************************************************
 * Function Name:       parse
 * The Input:           null
 * The Output:          null
 * Function Operation:  The function goes over all the text, parse it and execute all the commands.
 ****************************************************/
void Parser::parse() {
    vector<string> linesVector = Lexer::fromTextFileToVectorOfLines(path);
    for (int i = 0; i < linesVector.size(); i++) {
        Command* cmd;
        string currentLine = linesVector[i];
        vector<string> splittedLine = Lexer::fromLineToVectorOfStrings(currentLine);
        //If the line starts with "if" or "while" we extract the entire condition block.
        if ((splittedLine[0] == "if") || (splittedLine[0] == "while")) {
            vector<string> conditionBlock = Lexer::returnConditionBlock(linesVector, i);
            i += conditionBlock.size() - 1;
            cmd = this->getConditionCommand(conditionBlock);
            cmd->execute(conditionBlock);
        } else {
            cmd = this->getCommand(splittedLine);
            cmd->execute(splittedLine);
        }
    }
}

/****************************************************
 * Function Name:       ~Parser
 * The Input:           null
 * The Output:          null
 * Function Operation:  Parser destructor.
 ****************************************************/
Parser::~Parser() {
    delete((ExitCommand*) this->cmdMap["exit"]);
}