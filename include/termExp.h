#ifndef TERMEXP_H
#define TERMEXP_H

#include "./node.h"
#include "./term.h"

class TermExp : public Node {
public:
    TermExp(Term* term);
    void interpret(string text);
    bool evaluate();
    void clear();
private:    
    Term *_term;
};

#endif