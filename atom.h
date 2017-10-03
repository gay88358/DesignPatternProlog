#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;
class Variable;
class Number;
class Atom {
public:
  Atom (string s);
  string symbol();
  bool match(Number n); 
  bool match(Atom a);  
  bool match(Variable &v);
private:
  string _symbol;
};

#endif
