#ifndef NULLITERATOR_H
#define NULLITERATOR_H
#include "./iterator.h"

class NullIterator : public Iterator {
public:
    NullIterator(Term*);
    Term * currentItem();
private:
    Term *_term;
};

#endif