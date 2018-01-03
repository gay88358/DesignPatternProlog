#ifndef MATCHEXP_H
#define MATCHEXP_H

#include "./node.h"
#include "./term.h"
class MatchExp : public Node {
public:
    MatchExp(Node *left, Node *right);
    MatchExp(Term *left, Term *right);
    bool evaluate();
    string symbol();

private:
    Node *_left;
    Node *_right;
    Term *_leftTerm;
    Term *_rightTerm;
};

#endif