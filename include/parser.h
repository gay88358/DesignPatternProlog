#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include "./scanner.h"
#include "./term.h"
#include "./global.h"
#include "./variable.h"
#include "./atom.h"
#include "./number.h"
#include "./token.h"
#include "./builder.h"
#include "./struct.h"
#include "./list.h"

using std::vector;
using std::cout;
using std::endl;

class Parser {
public:
    Parser(Scanner scanner);
    Term* createTerm();
    void construct(Builder *builder);    
    vector<Term*> getArgs();    
private:
    Token* _currentToken;
    Scanner _scanner;
    Global _g;
    Builder* _builder;
};


#endif
