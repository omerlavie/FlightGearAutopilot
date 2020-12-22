#include <iostream>
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectToServerCommand.h"
#include "Lexer.h"
#include "VarCollection.h"
#include "Expression.h"
#include "Plus.h"
#include "Mul.h"
#include "Div.h"
#include "Parser.h"

int main(int argc, char* argv[]) {
    // create a new parser by the file path from argv.
    string path = argv[1];
    Parser* parser = new Parser(path);
    // parse the script and delete parser.
    parser->parse();
    delete(parser);
}
