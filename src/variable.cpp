#include "../include/variable.h"
#include "../include/atom.h"
#include "../include/number.h"

Variable::Variable(string s) {
    this->_symbol = s;
    this->_type = "Variable";
}

string Variable::value() const { 
    if (_instance != NULL)
        return _instance->value();
    return this->_symbol;
}

bool Variable::match(Term &term) { // match still has some problem in string compare like "" and so on
    if (_instance == NULL) {
        if (term.type() == "List") {
            vector<Term*> args = term.args();
            for (int i = 0; i < args.size(); i++) 
                if (args[i] == this) 
                    return false;
        }

        if (&term != this) { // X = X
            _instance = & term;
        }
    } else {
        _instance->match(term);
    }
    return this->value() == term.value();
}