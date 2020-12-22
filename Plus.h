#ifndef MILESTONE1_PLUS_H
#define MILESTONE1_PLUS_H

#include "BinaryExpression.h"
#include "Number.h"
#include "Minus.h"
#include "Mul.h"
#include "Div.h"

class Plus : public BinaryExpression {

public:
    Plus(Expression* e1, Expression* e2);
    string getType();
    double calculate();
    ~Plus();
};

#endif //MILESTONE1_PLUS_H
