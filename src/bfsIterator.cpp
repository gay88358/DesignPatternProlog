#include "../include/bfsIterator.h"
#include "../include/term.h"
#include <iostream>
using std::cout;
using std::endl;

BFSIterator::BFSIterator(Term * t): _term(t) {
    this->_isDone = false;
}

Term * BFSIterator::currentItem() {
    return this->_currentTerm;
}

bool BFSIterator::isDone() {
    return this->_isDone;
}

// createBFSIterator
void BFSIterator::next() {
    Term * term = this->_queue.front();
    if (term != NULL) {
        this->_currentTerm = term;
        this->_queue.pop();
        vector<Term *> args = term->args();
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

void BFSIterator::first() {
    vector<Term*> args = this->_term->args();
    for (int i = 0; i < args.size(); i++) {
        this->_queue.push(args[i]);
    }
    this->next();
}
