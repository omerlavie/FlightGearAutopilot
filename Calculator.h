#ifndef MILESTONE1_CALCULATOR_H
#define MILESTONE1_CALCULATOR_H

#include "Lexer.h"
#include "VarCollection.h"
#include "Expression.h"
#include "Number.h"
#include "Plus.h"
#include "Minus.h"
#include "Mul.h"
#include "Div.h"
#include "stack"

class Calculator {
private:
    static vector<string> shuntingYard(vector <string> v);
    static int getOperatorPrecedence(string o);
    static Expression* createExpressionByReversePolishNotation(vector<string> q, VarCollection* vc);

public:
    static double calculateExpression(string s, VarCollection* vc);
};

#endif //MILESTONE1_CALCULATOR_H
