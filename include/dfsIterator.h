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
    DFSIterator(Item term):_term(term) {
    }

    Item currentItem() {
        return this->_s.top()->currentItem();
    }

    bool isDone() {
        if (this->_s.empty())
            return true;
        return this->_s.top()->isDone();
    }

    void next() {
        Iterator<Item> *it = this->_s.top();
        if (!it->isDone()) {
            Iterator<Item>* innerIt = it->currentItem()->createIterator();
            innerIt->first();
            it->next();
            if (it->isDone())
                this->_s.pop();
            if (!innerIt->isDone())
                this->_s.push(innerIt);
        }
    }   

    void first() {
        Iterator<Item> *it = this->_term->createIterator();
        it->first();
        this->_s.push(it);
    }

    ~DFSIterator() {
    }
private:
    Item _term;
    Item _currentTerm;
    stack<Item> _stack;
    stack<Iterator<Item>*> _s;
};

#endif