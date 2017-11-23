#include "../include/builder.h"
Builder::Builder() {

}

Term * Builder::createVariable(string symbol) {
    return new Variable(symbol);
}

Term * Builder::createAtom(string symbol) {
    return new Atom(symbol);
}

Term * Builder::createNumber(double number) {
    return new Number(number);
}

Term * Builder::createStruct(string symbol, vector<Term*> args) {
    return new Struct(Atom(symbol), args);
}

Term * Builder::createList(vector<Term*> args) {
    return new List(args);
}




