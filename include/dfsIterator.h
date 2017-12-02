#ifndef DFSITERATOR_H
#define DFSITERATOR_H

#include "./iterator.h"
#include "./struct.h"
#include "./term.h"
#include <vector>
#include <stack>
using std::vector;
using std::stack;

class DFSIterator : public Iterator {
public:
    DFSIterator(Term *);
    Term * currentItem();
    bool isDone();
    void next();
    void first();
private:
    Term * _term;
    Term * _currentTerm;
    bool _isDone;
    stack<Term*> _stack;
};

#endif