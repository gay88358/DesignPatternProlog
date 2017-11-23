#ifndef ANDEXP_H
#define ANDEXP_H

#include "./node.h"

class AndExp : public Node {
public:
    AndExp(Node *left, Node *right);
    void interpret(string text);
    bool evaluate();
    void clear();
private:
    Node *_left;
    Node *_right;
};

#endif