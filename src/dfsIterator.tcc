#include "../include/dfsIterator.h"
#include <iostream>

using std::cout;
using std::endl;

template<class Item>
DFSIterator<Item>::DFSIterator(Item term):_term(term) {
    this->_isDone = false;
}

template<class Item>
Item DFSIterator<Item>::currentItem() {
    return this->_currentTerm;
}

template<class Item>
bool DFSIterator<Item>::isDone() {
    return this->_isDone;
}

template<class Item>
void DFSIterator<Item>::next() {
    Item term = NULL;
    if (!this->_stack.empty())
        term =  this->_stack.top();
    if (term != NULL) {
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

template<class Item>
void DFSIterator<Item>::first() {
    vector<Item> args = this->_term->args();
    for (int i = args.size() - 1; i >= 0; i--) {
        this->_stack.push(args[i]);
    }
    this->next();
}

template<class Item>
DFSIterator<Item>::~DFSIterator() {
    std::cout << "dfsIterator delete" << std::endl;
}




