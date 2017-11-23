#ifndef MATCHEXP_H
#define MATCHEXP_H

#include "./node.h"
#include "./term.h"
class MatchExp : public Node {
public:
    MatchExp(Node *left, Node *right);
    bool evaluate();
private:
    Node *_left;
    Node *_right;
};

#endif