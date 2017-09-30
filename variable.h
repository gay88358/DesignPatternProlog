#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
using std::string;

class Variable{
public:
  Variable(string s): _symbol(s) {}
  string symbol() { return this->_symbol; }
  string value(){ return this->_value; }
  bool match(Atom atom) {
      bool assign = false;
      if (_value.empty() || atom.symbol() == _value) {
        _value = atom.symbol();
        assign = true;
      }
      return assign;
  }
private:
  string _value;
  string _symbol;
};

#endif
