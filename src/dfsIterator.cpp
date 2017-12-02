#include "../include/dfsIterator.h"
#include <iostream>

using std::cout;
using std::endl;

DFSIterator::DFSIterator(Term *term):_term(term) {
    this->_isDone = false;
}

Term * DFSIterator::currentItem() {
    return this->_currentTerm;
}

bool DFSIterator::isDone() {
    return this->_isDone;
}

void DFSIterator::next() {
    Term * term = NULL;
    if (!this->_stack.empty())
        term =  this->_stack.top();
    if (term != NULL) {
        this->_currentTerm = term;
        this->_stack.pop();
        vector<Term *> args = term->args();
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

void DFSIterator::first() {
    vector<Term*> args = this->_term->args();
    for (int i = args.size() - 1; i >= 0; i--) {
        this->_stack.push(args[i]);
    }
    this->next();
}
