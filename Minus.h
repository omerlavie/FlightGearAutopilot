#ifndef MILESTONE1_MINUS_H
#define MILESTONE1_MINUS_H

#include "BinaryExpression.h"
#include "Number.h"
#include "Plus.h"
#include "Mul.h"
#include "Div.h"

class Minus : public BinaryExpression {

public:
    string getType();
    Minus(Expression* e1, Expression* e2);
    double calculate();
    ~Minus();
};


#endif //MILESTONE1_MINUS_H
