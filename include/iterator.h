#ifndef ITERATOR_H
#define ITERATOR_H

template<class Item>
class Iterator {
public:
    virtual Item currentItem() = 0;
    virtual bool isDone();
    virtual void next();
    virtual void first();
private:
};

#include "../src/iterator.tcc"
#endif