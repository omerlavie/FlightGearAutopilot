#include "Plus.h"

/****************************************************
 * Function Name:       constructor.
 * The Input:           left expression, right expression.
 * The Output:
 * Function Operation:  constructs a binary expresssion of adding.
 ****************************************************/
Plus::Plus(Expression* e1, Expression* e2) {
    this->right = e1;
    this->left = e2;
}

/****************************************************
 * Function Name:       calculate.
 * The Input:
 * The Output:          double result.
 * Function Operation:  calculates (left + right)
 ****************************************************/
double Plus::calculate(){
    return this->right->calculate() + this->left->calculate();
}