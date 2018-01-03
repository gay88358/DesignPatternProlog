#include "../include/orExp.h"
#include <iostream>

using std::cout;
using std::endl;

OrExp::OrExp(Node *left, Node *right): _left(left), _right(right) {
    this->payload = ";";
    this->left = left;
    this->right = right;
}

bool OrExp::evaluate() {
    bool left_val = this->_left->evaluate();
    bool right_val = this->_right->evaluate();
    return left_val || right_val;
}

string OrExp::symbol() {
    string leftSymbol = _left->symbol();
    string rightSymbol = _right->symbol();
    if (leftSymbol.empty() && rightSymbol.empty() == false)
        return rightSymbol;
    if (leftSymbol.empty() == false && rightSymbol.empty() == true)
        return leftSymbol;
        
    return _left->symbol() + "; " + _right->symbol();
}