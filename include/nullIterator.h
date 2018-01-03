#ifndef NULLITERATOR_H
#define NULLITERATOR_H

#include "./iterator.h"

template<class Item>
class NullIterator : public Iterator<Item> {
public:
    NullIterator(Item term): _term(term) {

    }
    Item currentItem() {
        return this->_term;
    }
private:
    Item _term;
};
#endif