#include "../include/matchExp.h"
#include <iostream>
using std::cout;
using std::endl;

MatchExp::MatchExp(Node *left, Node *right): _left(left), _right(right) {
    this->payload = "=";
    this->right = _right;
    this->left = _left;
}

MatchExp::MatchExp(Term *left, Term *right): _leftTerm(left), _rightTerm(right) {
    this->payload = "=";
}

bool MatchExp::evaluate() {
    return this->_leftTerm->match(*this->_rightTerm);
}

string MatchExp::symbol() {
    if (_leftTerm == _rightTerm) // same reference
        return "true";
    return _leftTerm->symbol() + " = " + _rightTerm->value();
}
