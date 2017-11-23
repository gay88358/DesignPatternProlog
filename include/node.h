#ifndef NODE_H
#define NODE_H

#include <string>
#include "term.h"
using std::string;

class Node {
public:
    virtual void interpret(string text) = 0;
    virtual bool evaluate() = 0;
    virtual void clear();
    string payload;
    Term * term;
    Node* right;
    Node* left;
private:
    string _text;
};


#endif 