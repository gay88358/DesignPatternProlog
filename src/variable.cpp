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

bool Variable::isRepeat(vector<Term*> targetPath) {
    for (int i = 0; i < targetPath.size(); i++) {
        if (targetPath[i] == this) {
            return true;
        }
    }

    for (int i = 0; i < this->_path.size(); i++) {
        for (int j = 0; j < targetPath.size(); j++) {
            if (this->_path[i] == targetPath[j])
                return true;
        }
    }
    return false;
}

void Variable::clear() {
    this->_instance = NULL;
}

bool Variable::match(Term &term) { // match still has some problem in string compare like "" and so on
    if (_instance == NULL) {
        Variable *ps = dynamic_cast<Variable*>(&term);
        if (this == ps)
            return true;
        if (ps) {
            // check match target if target repeat in list, then it will result recursive loop
            // if no recursive loop then instantiated it
            if (isRepeat(ps->_path)) {
                return true;
            } else {
                _instance = &term;
                this->_path.push_back(ps);
                ps->_path.push_back(this);
            }
        }
        else
            _instance = &term;
        return true;        
    } else {
        return _instance->match(term);
    }
}