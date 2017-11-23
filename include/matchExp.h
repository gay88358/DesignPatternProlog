#ifndef MATCHEXP_H
#define MATCHEXP_H

#include "./node.h"
#include "./term.h"
class MatchExp : public Node {
public:
    MatchExp(Node *left, Node *right);
    void interpret(string text);
    bool evaluate();
    void clear();
private:
    Node *_left;
    Node *_right;
};

#endif