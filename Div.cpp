#include "Div.h"

/****************************************************
 * Function Name:       constructor.
 * The Input:           left expression, right expression.
 * The Output:          null
 * Function Operation:  constructs a binary expresssion of diversion.
 ****************************************************/
Div::Div(Expression* e1, Expression* e2) {
    this->right = e1;
    this->left = e2;
}

/****************************************************
 * Function Name:       calculate.
 * The Input:           null
 * The Output:          double result.
 * Function Operation:  calculates (left / right)
 ****************************************************/
double Div::calculate(){
    return this->right->calculate() / this->left->calculate();
}