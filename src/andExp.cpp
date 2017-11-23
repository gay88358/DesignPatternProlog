#include "../include/andExp.h"

AndExp::AndExp(Node *left, Node *right): _left(left), _right(right) {
    this->payload = ",";
    this->left = left;
    this->right = right;
}

void AndExp::interpret(string text) {

}

bool AndExp::evaluate() {
    return this->_left->evaluate() && this->_right->evaluate();
}


void AndExp::clear() {
    this->_left->clear();
    this->_right->clear();
}
