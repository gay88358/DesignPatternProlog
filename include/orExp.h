#ifndef OREXP_H
#define OREXP_H

#include "./node.h"

class OrExp : public Node {
public:
    OrExp(Node *left, Node *right);
    bool evaluate();
private:
    Node *_left;
    Node *_right;
};

#endif