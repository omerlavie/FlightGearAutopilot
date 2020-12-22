#include "Calculator.h"

/****************************************************
 * Function Name:       getOperatorPrecedence.
 * The Input:           string o: An arithmetic sign (+,-,*,/).
 * The Output:          int precedence: the precedence of an arithmetic operation.
 * Function Operation:  The function returns the precedence of an arithmetic operation.
 ****************************************************/
int Calculator::getOperatorPrecedence(string o) {
    if(o == "+") {
        return 0;
    } else if (o == "-") {
        return 1;
    }else if (o == "*" || o == "/") {
        return 2;
        // parenthesis are top priority.
    } else if (o == "(" || o == ")") {
        return 3;
    }
}

/****************************************************
 * Function Name:       shuntingYard.
 * The Input:           vector <string>  v: a vector of infix notation equation with numbers only.
 * The Output:          vector <string>* q: a new vector with the numbers in the revers Polish notation.
 * Function Operation:  The function implements the shunting yard algorithm on a vector of strings.
 ****************************************************/
vector<string> Calculator::shuntingYard(vector <string> v) {
    stack <string> s;
    vector <string> q;
    for(int i = 0; i <v.size(); i++) {
        string token = v.at(i);
        // If it's a number add it to queue
        if(Lexer::isNumber(token)) {
            q.push_back(token);
            // If it's an operator
        } else if(Lexer::isOperator(token)) {
            // While there's an operator on the top of the stack with greater precedence
            while(!s.empty() && (Lexer::isOperator(s.top())) &&
                  (getOperatorPrecedence(s.top()) > getOperatorPrecedence(token))) {
                // Pop operators from the stack onto the output queue
                q.push_back(s.top());
                s.pop();
            }
            // Push the current operator onto the stack
            s.push(token);
        }
            // If it's a left bracket push it onto the stack
        else if(token == "(") {
            s.push(token);
        }
            // If it's a right bracket
        else if (token == ")") {
            // While there's not a left bracket at the top of the stack
            while(!s.empty() && s.top() != "(") {
                // Pop operators from the stack onto the output queue
                q.push_back(s.top());
                s.pop();
            }
            // Pop the left bracket from the stack and discard it
            if(!s.empty()) {
                s.pop();
            }
        }
    }
    //Empty the stack from any left bracket.
    while(!s.empty()) {
        if(s.top() == "(" || s.top() == ")") {
            string error = "error: there are mismatched parentheses.";
            throw(error);
        } else {
            q.push_back(s.top());
            s.pop();
        }
    }
    return q;
}

/****************************************************
 * Function Name:       createExpressionByReversePolishNotation.
 * The Input:           vector <string>  q: a vector of numbers and operators in reverse polish notation.
 * The Output:          Expression* e: an expression created by the vector.
 * Function Operation:  The function implements an algorithm that uses a reverse polish notation to set the elements
 *                      in the right order.
 ****************************************************/
Expression* Calculator::createExpressionByReversePolishNotation(vector<string> q, VarCollection* vc) {
    stack <Expression*> s;
    // iterate the vector.
    for(int i = 0; i < q.size(); i++) {
        string temp_token = q.at(i);
        // if current token is a number, create a Number object of it and push it into the stack.
        if(Lexer::isNumber(temp_token)) {
            Number* token = new Number(Lexer::stringToDouble(temp_token));
            vc->addToDestructionList(token);
            s.push(token);
        } else {
            Expression* y = s.top();
            s.pop();
            Expression* x = s.top();
            s.pop();
            // create the expression that matches the operator and push it into the stack.
            if(temp_token == "+") {
                Plus* plus = new Plus(x, y);
                s.push(plus);
                vc->addToDestructionList(plus);
            }
            else if(temp_token == "-") {
                Minus* minus = new Minus(x, y);
                vc->addToDestructionList(minus);
                s.push(minus);
            }
            else if(temp_token == "*") {
                Mul* mul = new Mul(x, y);
                vc->addToDestructionList(mul);
                s.push(mul);
            }
            else if(temp_token == "/") {
                Div* div = new Div(x, y);
                vc->addToDestructionList(div);
                s.push(div);
            }
        }
    }
    Expression* ex = s.top();
    s.pop();
    // there should be a single element in the stack in the end. return it.
    return ex;
}

/****************************************************
 * Function Name:       calculateExpression.
 * The Input:           string s: the expression as a string.
 *                      VarCollection* vc: the variable collection object.
 * The Output:          Expression* e: an expression created by the vector.
 * Function Operation:  operates the proccess of calculating the result of an expression string.
 *                      first it separates the parts of the expression to substrings and pushes it to a vector,
 *                      then it replaces the variable names by their values (using the var map), and using shunting yard
 *                      to get an Expression* object of the expression. final step is calculating the result by using
 *                      the reverse polish notation of the expression.
 ****************************************************/
double Calculator::calculateExpression(string s, VarCollection* vc) {
    map<string, pair<string, double>> varMap = vc->getVariablesMap();
    // create a fixed vector with separated elements based on the string.
    vector<string> fixedv = Lexer::expressionStringToFixedVector(s);
    // pass fixed vector to replaceVarNamesByValues to replace variable names by their actual values.
    Lexer::replaceVarNamesByValues(&fixedv, varMap);
    // pass fixedv to shunting yard algorithm to get a reverse polish notation vector of it.
    vector<string> rpn = shuntingYard(fixedv);
    // create an expression with reverse polish notation algorithm.
    Expression* exp = createExpressionByReversePolishNotation(rpn, vc);
    // calculate the value of the expression.
    double result = exp->calculate();
    return result;
}
