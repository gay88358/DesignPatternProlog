#include "number.h"
#include "atom.h"
#include "variable.h"

Number::Number(int value) : _value(value), _symbol(std::to_string(this->_value)) {

}

string Number::symbol() { 
    return this->_symbol;
}

int Number::value() { 
    return this->_value; 
}

bool Number::match(Number n) { 
    return this->_value == n.value(); 
}

bool Number::match(Atom n) { 
    return false; 
}  

bool Number::match(Variable &v) {
    return v.match(*this);
}  