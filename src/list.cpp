#include "../include/list.h"
#include <iostream>

List::List (): _elements() { // default constructor
    this->_type = "List";        
}

List::List (vector<Term *> const & elements):_elements(elements) {
    this->_type = "List";        
}

int List::argSize() const {
    return this->_elements.size();
}

vector<Term*> List::args() const {
    return this->_elements;
}

string List::symbol() const {
    if (this->_elements.size() == 0) return "[]";
    string symbol = "[";
    for (int i = 0; i < this->_elements.size() - 1; i++)
        symbol += this->_elements[i]->symbol() + ", ";
    symbol += this->_elements[this->_elements.size() - 1]->symbol() + "]";
    return symbol;
}

string List::value() const {
    if (this->_elements.size() == 0) return "[]";
    string value = "[";
    for (int i = 0; i < this->_elements.size() - 1; i++)
        value += this->_elements[i]->value() + ", ";
    value += this->_elements[this->_elements.size() - 1]->value() + "]";
    return value;
}

bool List::match(Term & term) {
    bool assign = false;
    if (this->_type == term.type() && this->argSize() == term.argSize()) { // list match list and size must be same
        vector<Term*> term_vector = term.args();
        for (int i = 0; i < this->_elements.size(); i++) {
            if (!this->_elements[i]->match(*term_vector[i]))
                return assign;
        }
        assign = true;
    }
    if ("Variable" == term.type()) {
        term.match(*this);
    }
    return assign;
}

Term * List::head() const{
    if (this->_elements.empty()) {
        //throw string("Accessing head in an empty list");
    }
    Term *h = this->_elements[0];
    return h;
}

List * List::tail() {
    if (this->_elements.empty()) {
        //throw string("Accessing tail in an empty list");
    }

    vector<Term*>::iterator f = this->_elements.begin() + 1;
    vector<Term*>::iterator l = this->_elements.end();
    return new List(vector<Term *>(f, l));
}