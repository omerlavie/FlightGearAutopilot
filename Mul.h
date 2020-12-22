#ifndef MILESTONE1_MUL_H
#define MILESTONE1_MUL_H

#include "BinaryExpression.h"
#include "Number.h"
#include "Plus.h"
#include "Div.h"
#include "Minus.h"

class Mul : public BinaryExpression {

public:
    string getType();
    Mul(Expression* e1, Expression* e2);
    double calculate();
    ~Mul();
};


#endif //MILESTONE1_MUL_H
