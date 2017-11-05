#ifndef BUILDER_H
#define BUILDER_H

#include "./term.h"
#include "./atom.h"
#include "./variable.h"
#include "./number.h"
#include "./global.h"
#include "./token.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
class Builder {
public:
    Builder();
    Term* getTerm(Token *token);
    virtual void buildTerm(Token *token);
    virtual Term* getTerm();
protected:
    Term * _term;
    Global _g;
};

#endif