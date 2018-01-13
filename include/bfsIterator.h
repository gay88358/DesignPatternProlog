#ifndef BFSITERATOR_H
#define BFSITERATOR_H

#include "./iterator.h"
#include "./nullIterator.h"
#include <vector>
#include <queue>
#include <iostream>
using std::cout;
using std::endl;

using std::vector;
using std::queue;
template <class Item>
class BFSIterator : public Iterator<Item> {
public:
    BFSIterator(Item t): _term(t) {
        this->_isDone = false;
    }

    Item currentItem() {
        return this->_q.front()->currentItem();
    }

    bool isDone() {
        if (this->_q.empty())
            return true;
        return this->_q.front()->isDone();
    }

    void next() {
        Iterator<Item> *it = this->_q.front();
        if (!it->isDone()) {
            Iterator<Item>* innerIt = it->currentItem()->createIterator();
            innerIt->first();
            if (!innerIt->isDone())
                this->_q.push(innerIt);

            it->next();

            if (it->isDone())
                this->_q.pop();
        } 
    } 

    void first() {
        Iterator<Item> *it = this->_term->createIterator();
        it->first();
        this->_q.push(it);
    }

    ~BFSIterator() {
    }
private:
    Item _term;
    Iterator<Item> *_currentIt;
    queue<Item> _queue;
    queue<Iterator<Item>*> _q;
    Item _currentTerm;
    bool _isDone;
};

#endif