#ifndef NUMBER_H
#define NUMBER_H
#include <string>

using std::string;

class Number {
public:
    Number(string s) : _symbol(s) {}
    string symbol() { return this->_symbol; }
    string value() { return this->_value; };
private:
    string _value;
    string _symbol;
};

#endif