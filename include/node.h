#ifndef NODE_H
#define NODE_H

#include <string>
#include "term.h"
using std::string;

class Node {
public:
    virtual bool evaluate() = 0;
    virtual string symbol() = 0;
    string payload;
    Term * term;
    Node* right;
    Node* left;
private:
    string _text;
};


#endif 