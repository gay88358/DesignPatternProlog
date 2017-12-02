#ifndef BFSITERATOR_H
#define BFSITERATOR_H

#include "./iterator.h"
#include <queue>

using std::queue;
class Term;
class BFSIterator : public Iterator {
public:
    BFSIterator(Term *);
    Term * currentItem();
    bool isDone();
    void next();
    void first();
private:
    Term* _term;
    Iterator *_currentIt;
    queue<Term*> _queue;
    Term * _currentTerm;
    bool _isDone;
};

#endif