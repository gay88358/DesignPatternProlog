#include "../include/matchExp.h"

MatchExp::MatchExp(Node *left, Node *right): _left(left), _right(right) {
    this->payload = "=";
    this->right = _right;
    this->left = _left;
}
    
void MatchExp::interpret(string text) {

}

bool MatchExp::evaluate() {
    return this->_left->term->match(*this->_right->term);
}

void MatchExp::clear() {
    this->_left->term->clear();
    this->_right->term->clear();
}

