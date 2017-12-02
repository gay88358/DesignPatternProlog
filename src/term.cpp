#include "../include/term.h"
#include "../include/variable.h"
#include "../include/dfsIterator.h"
#include "../include/bfsIterator.h"

#include <iostream>

string Term::symbol() const {
    return this->_symbol;
}    

string Term::value() const {
    return symbol();
}

bool Term::match(Term &term) {
    if (term.type() == "Variable")
        return term.match(*this);
    return _symbol == term._symbol;
}

Term* Term::name() {
    return NULL;
}

string Term::type() const {
    return this->_type;
}

int Term::argSize() const {
    return 0;
}

vector<Term*> Term::args() const {
    vector<Term*> v;
    return v;
}

void Term::clear() {
    // do nothing
}

Iterator* Term::createDFSIterator() {
    return new DFSIterator(this);
}

Iterator* Term::createBFSIterator() {
    return new BFSIterator(this);
}


Term* Term::find(string symbol) {
    if (this->_symbol == symbol) {
        return this;
    }
    return NULL;
}

Iterator* Term::createIterator() {
    return new NullIterator(this);
}
