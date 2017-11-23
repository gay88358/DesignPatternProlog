#ifndef BUILDER_H
#define BUILDER_H

#include "./term.h"
#include "./atom.h"
#include "./variable.h"
#include "./number.h"
#include "./global.h"
#include "./token.h"
#include "./list.h"
#include "./struct.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
class Builder {
public:
    Builder();
    Term * createVariable(string symbol);
    Term * createAtom(string symbol);
    Term * createNumber(double number);
    Term * createStruct(string symbol, vector<Term*> args);
    Term * createList(vector<Term*> args);
protected:
    Global _g;
};

#endif