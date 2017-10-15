#include "../include/struct.h"
#include "../include/atom.h"
#include "../include/term.h"
#include <iostream>

Struct::Struct(Atom name, vector<Term*> args) : _name(name), _args(args) {
}

Atom Struct::name() const {
    return this->_name;
}

Term* Struct::args(int index) const{
    return this->_args[index];
}

int Struct::length() {
    return this->_args.size();
}

string Struct::value() const {
    string value = this->_name.symbol() + "(";
    for (int i = 0; i < this->_args.size() - 1; i++) {
        value += this->_args[i]->value() + ", "; 
    }    
    value += this->_args[this->_args.size() - 1]->value() + ")";
    return value;
}
 
string Struct::symbol() const {
    string symbol = this->_name.symbol() + "(";
    for (int i = 0; i < this->_args.size() - 1; i++) {
        symbol += this->_args[i]->symbol() + ", "; 
    }
    symbol += this->_args[this->_args.size() - 1]->symbol() + ")";
    return symbol;
}

bool Struct::match(Term &term) {
    bool assign = false;
    Struct *s = dynamic_cast<Struct *>(&term);
    if (s) { // term is a struct
        if (!s->_name.match(this->_name) || _args.size() != s->_args.size()) 
            // the functor of struct different
            // the size of args of struct different 
            return assign;

        for (int i = 0; i < this->_args.size(); i++) {
            // once the symbol of args is different then return false 
            if (this->_args[i]->symbol() != s->_args[i]->symbol())
                return assign;
        }
        assign = true;
    }
    return assign;
}