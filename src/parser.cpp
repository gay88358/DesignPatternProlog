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
    this->_fly->findTerms(term);
    args.push_back(this->_fly->getCurrentTerm());

    while (!this->createTerm() && _currentToken->tokenValue() == ",") { // not null && value is ', '
        this->_fly->findTerms(this->createTerm());
        args.push_back(this->_fly->getCurrentTerm());
    }
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

void Parser::matchings() {
    this->_fly->pushOrNode(this->term());
    while (this->_currentToken->tokenValue() == ";") {
        // copy term in the tempterms and insert all terms in the terms
        // clear all temp terms
        this->_fly->addIndex(); // when encounter the comma, crete new vector of item
        this->_fly->pushOrNode(this->term());
    }
    this->_expTree = this->_fly->getOrNode();
}

Node* Parser::factor() {
    this->_fly->addTerms(this->createTerm());
    Term *left_term = this->_fly->getCurrentTerm();

    this->createTerm(); // extract equal token
    
    this->_fly->addTerms(this->createTerm());
    Term *right_term = this->_fly->getCurrentTerm();
    
    this->createTerm();
    return new MatchExp(new TermExp(left_term), new TermExp(right_term));
}

Node* Parser::term() {
    this->_fly->pushAndNode(this->factor());

    while (this->_currentToken->tokenValue() == ",")
        this->_fly->pushAndNode(this->factor());
    
    return this->_fly->getAndNode();
}

vector<Term *> Parser::getTerms() {
    return this->_fly->getargs();
}

Node* Parser::expressionTree() {
    return this->_expTree;
}
