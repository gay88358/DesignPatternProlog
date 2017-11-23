#include "../include/orExp.h"
#include <iostream>

using std::cout;
using std::endl;

OrExp::OrExp(Node *left, Node *right): _left(left), _right(right) {
    this->payload = ";";
    this->left = left;
    this->right = right;
}

void OrExp::interpret(string text) {

}

void OrExp::clear() {
    OrExp *orExp = dynamic_cast<OrExp*>(this->_left);
    
    if (orExp) { // type is OrExp
        cout << "fucking bug" << endl;
        orExp->_left->clear();
        orExp->_right->clear();
    } else {
        throw string("??");
    }
}  

bool OrExp::evaluate() {
    bool left_val = this->_left->evaluate();
    // clear all proxy instance of all item which's type is variable 
    bool right_val = this->_right->evaluate();
    //
    cout << "right val: " << right_val << endl;
    return left_val || right_val;
}


