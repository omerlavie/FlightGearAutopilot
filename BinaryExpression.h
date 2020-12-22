#ifndef MILESTONE1_BINARYEXPRESSION_H
#define MILESTONE1_BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression {
protected:
    Expression* right;
    Expression* left;
};

#endif //MILESTONE1_BINARYEXPRESSION_H
