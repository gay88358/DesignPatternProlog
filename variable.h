#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

using std::string;

class Atom;
class Number;
class Variable{
public:
  Variable(string s);
  string symbol(); 
  string value();
  bool match(Number n);
  bool match(Atom atom);
private:
  string _value;
  string _symbol;
};

#endif
