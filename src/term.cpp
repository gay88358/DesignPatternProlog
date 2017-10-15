#include "../include/term.h"
#include "../include/variable.h"
#include <iostream>

string Term::symbol() const {
    return this->_symbol;
}    

string Term::value() const {
    return symbol();
}

bool Term::match(Term &term) {
    Variable *v = dynamic_cast<Variable *>(&term);
    if (v) {
        std::cout << "variable" << std::endl;
        return v->match(*this);
    }
    return _symbol == term._symbol;
}
