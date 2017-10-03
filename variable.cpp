#include "variable.h"
#include "atom.h"
#include "number.h"

Variable::Variable(string s): _symbol(s) {

}
string Variable::symbol() { 
    return this->_symbol; 
}
string Variable::value() { 
    return this->_value; 
}

bool Variable::match(Number n) {
  bool assign = false;
  if (_value.empty() || n.symbol() == _value) {
    _value = n.symbol();
    assign = true;
  }
  return assign;
}

bool Variable::match(Atom atom) {
    bool assign = false;
    if (_value.empty() || atom.symbol() == _value) {
      _value = atom.symbol();
      assign = true;
    }
    return assign;
}

bool Variable::match(Variable &v) {
    bool assign = false;
    if (this->_value.empty()) { // not assign
        if (v.value().empty()) {
            
        } else {
            this->_value = v.value();
            assign = true;
        }
    } else { // assign
        if (v.value().empty()) { // y not assign
            v.match(*this);
            assign = true;
        } else {
            assign = false;
        }
    }
    return assign;
}