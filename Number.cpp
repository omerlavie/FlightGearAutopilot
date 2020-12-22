#include "Number.h"

/****************************************************
 * Function Name:       constructor.
 * The Input:           double v : value.
 * The Output:
 * Function Operation:  constructs a new Number object.
 ****************************************************/
Number::Number(double v) {
    this->value = v;
}

/****************************************************
 * Function Name:       calculate.
 * The Input:
 * The Output:          double result.
 * Function Operation:  returns the number's value in double.
 ****************************************************/
double Number::calculate() {
    return this->value;
}