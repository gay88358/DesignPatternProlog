#include "../include/struct.h"
#include "../include/atom.h"
#include "../include/term.h"
#include <iostream>

Struct::Struct(Atom name, vector<Term*> args) : _name(name), _args(args) {
    this->_type = "Struct";    
}

int Struct::argSize() const {
    return this->_args.size();
}

vector<Term*> Struct::args() const {
    return this->_args;
}

Term* Struct::args(int index) const{
    return this->_args[index];
}

Term* Struct::name() {
    return &this->_name;
}

int Struct::arity() {
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
    if (this->_args.size() == 0)
        return symbol + ")";
    for (int i = 0; i < this->_args.size() - 1; i++) {
        symbol += this->_args[i]->symbol() + ", "; 
    }
    symbol += this->_args[this->_args.size() - 1]->symbol() + ")";
    return symbol;
}

bool Struct::match(Term &term) {
    bool assign = false;
    if (_type == term.type()) {
        if (!term.name()->match(this->_name) || this->_args.size() != term.argSize())
            return assign;
        for (int i = 0; i < this->_args.size(); i++)
            if (this->_args[i]->symbol() != term.args()[i]->symbol())
                return assign;
        assign = true;
    }

    if (term.type() == "Variable")
        return term.match(*this);
    return assign;
}


Term* Struct::find(string symbol) {
    vector<Term*> args = this->_args;
    for (int i = 0; i < args.size(); i++) {
        Term *find = args[i]->find(symbol);
        if (find != NULL) {
            return find;
        }
    }
    return NULL;
}
