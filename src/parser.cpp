#include "../include/parser.h"
#include <iostream>
using std::cout;
using std::endl;
Parser::Parser(Scanner scanner): _scanner(scanner), _builder(new Builder), _fly(new FlyWeight) {
}

Term* Parser::createTerm() {
    // illegal
    if (!this->_scanner.isLegal())
        throw string("unexpected token");

    this->_currentToken = this->_scanner.nextToken();

    if (_currentToken->tokenType() == _g.VAR) {
        return this->_builder->createVariable(_currentToken->tokenValue());
    } else if (_currentToken->tokenType() == _g.ATOM) {        
        Term *atom = this->_builder->createAtom(_currentToken->tokenValue());
        if (this->_scanner.currentChar() != '(')
            return atom;
        string symbol = atom->symbol();
        this->_scanner.nextToken();
        return this->_builder->createStruct(symbol, this->getArgs());
    } else if (_currentToken->tokenType() == _g.NUMBER) {
        return this->_builder->createNumber(stod(_currentToken->tokenValue()));
    } else if (_currentToken->tokenValue() == "[") {
        return this->_builder->createList(this->getArgs());
    } else if (_currentToken->tokenValue() == ",") {
        return NULL;
    } else if (_currentToken->tokenValue() == ";") {
        return NULL;
    } else if (_currentToken->tokenValue() == ".") {
        return NULL;
    }
    else 
        return NULL;
}

vector<Term*> Parser::getArgs() {
    vector<Term*> args;
    Term *term = this->createTerm();
    if (term == NULL)  {
        return args;
    }
    else if (this->_currentToken->tokenValue() == ";" || this->_currentToken->tokenValue() == ",")
        throw string("Unbalanced operator");

    this->_fly->findTerms(term);
    args.push_back(this->_fly->getCurrentTerm());

    while (!this->createTerm() && _currentToken->tokenValue() == ",") { // not null && value is ', '
        Term * anotherTerm = this->createTerm();
        if (anotherTerm->symbol() == "," || anotherTerm->symbol() == ";")
            throw string("Unbalanced operator");

        this->_fly->findTerms(anotherTerm);
        args.push_back(this->_fly->getCurrentTerm());
    }

    if (_currentToken->tokenValue() == ";")
        throw string("Unbalanced operator");        
    return args;
}

void Parser::createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while(!this->createTerm() && _currentToken->tokenValue() == ",") {
        _terms.push_back(createTerm());
      }
    }
}

string Parser::getResult() {
    if (!this->_expTree->evaluate())
        return "false.";
    return this->_expTree->symbol() + ".";
}

void Parser::buildExpression() {
    this->_fly->pushOrNode(this->term());
    while (this->_currentToken->tokenValue() == ";") {
        // copy term in the tempterms and insert all terms in the terms
        // clear all temp terms
        this->_fly->addIndex(); // when encounter the comma, crete new vector of item
        this->_fly->pushOrNode(this->term());
    }
    if (this->_currentToken->tokenValue() != ".")
        throw string("Missing token '.'");

    this->_expTree = this->_fly->getOrNode();
}

Node* Parser::term() {
    this->_fly->pushAndNode(this->factor());

    while (this->_currentToken->tokenValue() == ",") {
        if (_scanner.currentChar() == '.')
            throw string("Unexpected ',' before '.'");
        this->_fly->pushAndNode(this->factor());
    }
        
    return this->_fly->getAndNode();
}

Node* Parser::factor() { // X = 1.
    this->_fly->addTerms(this->createTerm());
    Term *left_term = this->_fly->getCurrentTerm();

    this->createTerm(); // extract equal token
    string op = this->_currentToken->tokenValue();
    if (op != "=" && _scanner.currentChar() == '.')
        throw string("Unexpected '"+ op + "' before '.'");

    Term *term = this->createTerm();
    if (term != NULL)
        this->_fly->addTerms(term);
    else
        throw string(left_term->symbol() + " does never get assignment");

    Term *right_term = this->_fly->getCurrentTerm();

    this->createTerm();
    return new MatchExp(left_term, right_term);
}

vector<Term *> Parser::getTerms() {
    return this->_fly->getargs();
}

Node* Parser::expressionTree() {
    return this->_expTree;
}

bool Parser::isValidChar(char c) {
    return (c == ';' || c == ',');
}