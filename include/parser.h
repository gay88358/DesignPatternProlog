#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include "./node.h"
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
#include "./matchExp.h"
#include "./orExp.h"
#include "./andExp.h"
#include "./termExp.h"
#include "./flyWeight.h"
#include <stack>         

using std::stack;
using std::vector;
using std::cout;
using std::endl;

class Parser {
public:
    Parser(Scanner scanner);
    Term* createTerm();
    void buildExpression();
    //Node* expressionTree(); 
    vector<Term*> getArgs(); 
    vector<Term *> getTerms();
    void createTerms(); // ("X, Y") [X, Y]
    Node* factor();
    Node* term();
    Node* expressionTree();
    bool isValidChar(char c);
    string getResult();
private:
    vector<Term *> _terms;
    vector<Term *> _tempTerms;
    Token* _currentToken;
    Scanner _scanner;
    Global _g;
    Builder* _builder;
    Node * _expTree;
    FlyWeight* _fly;
};

#endif
