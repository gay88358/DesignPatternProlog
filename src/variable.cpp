#include "../include/variable.h"
#include "../include/atom.h"
#include "../include/number.h"

Variable::Variable(string s) {
    this->_symbol = s;
}

string Variable::value() const { 
    if (_instance != NULL)
        return _instance->value();
    return this->_symbol;
}

bool Variable::match(Term &term) { // match still has some problem in string compare like "" and so on
    if (_instance == NULL) {
        if (&term != this) { // X = X
            _instance = & term;
        }
    } else {
        _instance->match(term);
    }
    return this->value() == term.value();
}