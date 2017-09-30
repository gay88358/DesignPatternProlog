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
  if (_value.empty() || n.value() == _value) {
    _value = n.value();
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