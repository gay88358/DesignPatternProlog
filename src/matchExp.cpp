#include "../include/matchExp.h"

MatchExp::MatchExp(Node *left, Node *right): _left(left), _right(right) {
    this->payload = "=";
    this->right = _right;
    this->left = _left;
}

bool MatchExp::evaluate() {
    return this->_left->term->match(*this->_right->term);
}
