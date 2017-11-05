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

bool Variable::match(Term &term) { // match still has some problem in string compare like "" and so on
    /*if (_instance == NULL) {
        if (term.type() == "List") {
            vector<Term*> args = term.args();
            for (int i = 0; i < args.size(); i++) 
                if (args[i] == this) 
                    return false;
        }
        if (&term != this)
            _instance = &term;
        return true;    
    } else {
        if (term.symbol() == _instance->symbol() && &term == _instance) return true;        
        return _instance->match(term);        
    }*/
    
    /*if (_instance == NULL) {
        Variable *ps = dynamic_cast<Variable*>(&term);
        if (ps) {  // var match var
            if (this == ps)
                return true;
            // head empty
            if (ps->head.empty() && ps->symbol() != this->head) {
                if (this->head.empty()) 
                    ps->head = this->symbol();
                else 
                    ps->head = this->head;
                _instance = &term;
            }
        } else // var match other
            _instance = &term;
        return true;
    } else {
        return _instance->match(term);
    }*/

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