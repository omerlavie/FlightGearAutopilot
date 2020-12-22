#ifndef MILESTONE1_DIV_H
#define MILESTONE1_DIV_H

#include "BinaryExpression.h"
#include "Number.h"
#include "Plus.h"
#include "Mul.h"
#include "Minus.h"

class Div : public BinaryExpression {

public:
    string getType();
    Div(Expression* e1, Expression* e2);
    double calculate();
    ~Div();
};

#endif //MILESTONE1_DIV_H
