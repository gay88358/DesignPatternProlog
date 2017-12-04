#ifndef NULLITERATOR_H
#define NULLITERATOR_H

#include "./iterator.h"

template<class Item>
class NullIterator : public Iterator<Item> {
public:
    NullIterator(Item);
    Item currentItem();
private:
    Item _term;
};

#include "../src/nullIterator.tcc"
#endif