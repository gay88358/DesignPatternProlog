#include "../include/atom.h"
#include "../include/number.h"
#include "../include/variable.h"

Atom::Atom(string s) {
    this->_symbol = s;
    this->_type = "Atom";
}
