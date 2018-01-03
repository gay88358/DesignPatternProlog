#include "../include/andExp.h"

AndExp::AndExp(Node *left, Node *right): _left(left), _right(right) {
    this->payload = ",";
    this->left = left;
    this->right = right;
}

bool AndExp::evaluate() {
    return this->_left->evaluate() && this->_right->evaluate();
}

string AndExp::symbol() {
    if (evaluate() == false)
        return "";
    if (_left->symbol() == "true" &&  _right->symbol() == "true") 
        return "true";
    if (_left->symbol() == "true" && _right->symbol() != "true")
        return _right->symbol();
    if (_left->symbol() != "true" && _right->symbol() == "true")
        return _left->symbol();
    if (_left->symbol() == _right->symbol())
        return _left->symbol();
    
    return _left->symbol() + ", " + _right->symbol();
}

