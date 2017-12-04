#ifndef DFSITERATOR_H
#define DFSITERATOR_H

#include "./iterator.h"
#include <vector>
#include <stack>
using std::vector;
using std::stack;
template<class Item>
class DFSIterator : public Iterator<Item> {
public:
    DFSIterator(Item);
    Item currentItem();
    bool isDone();
    void next();
    void first();
private:
    Item _term;
    Item _currentTerm;
    bool _isDone;
    stack<Item> _stack;
};
#include "../src/dfsIterator.tcc"

#endif