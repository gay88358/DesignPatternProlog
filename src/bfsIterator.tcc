#include "../include/bfsIterator.h"

template<class Item>
BFSIterator<Item>::BFSIterator(Item t): _term(t) {
    this->_isDone = false;
}

template<class Item>
Item BFSIterator<Item>::currentItem() {
    return this->_currentTerm;
}

template<class Item>
bool BFSIterator<Item>::isDone() {
    return this->_isDone;
}

template<class Item>
// createBFSIterator
void BFSIterator<Item>::next() {
    Item term = this->_queue.front();
    if (term != NULL) {
        this->_currentTerm = term;
        this->_queue.pop();
        vector<Item> args = term->args();
        if (args.size() > 0)
        {
            for (int i = 0; i < args.size(); i++) {
                this->_queue.push(args[i]);
            }
        }
    } else {
        this->_isDone = true;
    }
} 

template<class Item>
void BFSIterator<Item>::first() {
    vector<Item> args = this->_term->args();
    for (int i = 0; i < args.size(); i++) {
        this->_queue.push(args[i]);
    }
    this->next();
}
