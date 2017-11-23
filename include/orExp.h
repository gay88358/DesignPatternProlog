#ifndef OREXP_H
#define OREXP_H

#include "./node.h"

class OrExp : public Node {
public:
    OrExp(Node *left, Node *right);
    void interpret(string text);
    bool evaluate();
    void clear();
private:
    Node *_left;
    Node *_right;
};

#endif