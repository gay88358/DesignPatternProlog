#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Atom {
public:
  Atom (string s):_symbol(s) {}
  string symbol() { return this->_symbol; }
  bool operator ==(Atom a) {return _symbol == a.symbol();}
private:
  string _symbol;
};

#endif
