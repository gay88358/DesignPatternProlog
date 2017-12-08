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
    /*DFSIterator(Item);
    Item currentItem();
    bool isDone();
    void next();
    void first();
    ~DFSIterator();*/
    DFSIterator(Item term):_term(term) {
        this->_isDone = false;
    }

    Item currentItem() {
        return this->_currentTerm;
    }

    bool isDone() {
        return this->_isDone;
    }

    void next() {
        Item term = nullptr;
        if (!this->_stack.empty())
            term =  this->_stack.top();
        if (term) {
            this->_currentTerm = term;
            this->_stack.pop();
            vector<Item> args = term->args();
            if (args.size() > 0)
            {
                for (int i = args.size() - 1; i >= 0; i--) {
                    this->_stack.push(args[i]);
                }
            }
        } else {
            this->_isDone = true;
        }
    }   

    void first() {
        vector<Item> args = this->_term->args();
        for (int i = args.size() - 1; i >= 0; i--) {
            this->_stack.push(args[i]);
        }
        this->next();
    }

    ~DFSIterator() {
    }

private:
    Item _term;
    Item _currentTerm;
    bool _isDone;
    stack<Item> _stack;
};
//#include "../src/dfsIterator.tcc"

#endif