#ifndef BFSITERATOR_H
#define BFSITERATOR_H

#include "./iterator.h"
#include <vector>
#include <queue>
using std::vector;
using std::queue;
template <class Item>
class BFSIterator : public Iterator<Item> {
public:
    BFSIterator(Item);
    Item currentItem();
    bool isDone();
    void next();
    void first();
    ~BFSIterator();
private:
    Item _term;
    Iterator<Item> *_currentIt;
    queue<Item> _queue;
    Item _currentTerm;
    bool _isDone;
};
#include "../src/bfsIterator.tcc"

#endif