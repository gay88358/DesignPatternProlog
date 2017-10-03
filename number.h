#ifndef NUMBER_H
#define NUMBER_H

#include <string>

using std::string;

class Atom;
class Variable;
class Number {
public:
    Number(int value); 
    string symbol(); 
    string value(); 
    bool match(Number n); 
    bool match(Atom n);
    bool match(Variable &v);
private:
    string _value;
    string _symbol;
};

#endif