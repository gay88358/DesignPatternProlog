#include "atom.h"
#include "number.h"
#include "variable.h"

Atom::Atom(string s): _symbol(s) {

}

string Atom::symbol() { 
    return this->_symbol; 
}

bool Atom::match(Number n) { 
    return false; 
}

bool Atom::match(Atom a) { 
    return _symbol == a.symbol(); 
}  

bool Atom::match(Variable *v) { 
    return v->match(_symbol); 
}