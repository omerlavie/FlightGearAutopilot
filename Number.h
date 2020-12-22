#ifndef MILESTONE1_NUMBER_H
#define MILESTONE1_NUMBER_H

#include "Expression.h"

class Number : public Expression {
private:
    // number's value.
    double value;

public:
    Number(double v);
    double calculate();
};

#endif //MILESTONE1_NUMBER_H
