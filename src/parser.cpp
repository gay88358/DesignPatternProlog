#include "../include/parser.h"
Parser::Parser(Scanner scanner): _scanner(scanner), _builder(new Builder) {
}

Term* Parser::createTerm() {
    // illegal
    if (!this->_scanner.isLegal())
        throw string("unexpected token");

    this->_currentToken = this->_scanner.nextToken();
    if (_currentToken->tokenType() == _g.VAR) {
        return new Variable(_currentToken->tokenValue());
    } else if (_currentToken->tokenType() == _g.ATOM) {        
        Atom *atom = new Atom(_currentToken->tokenValue());
        if (this->_scanner.currentChar() != '(')
            return atom;
        this->_scanner.nextToken();    
        return new Struct(*atom, this->getArgs());
    } else if (_currentToken->tokenType() == _g.NUMBER) {
        return new Number(stod(_currentToken->tokenValue()));        
    } else if (_currentToken->tokenValue() == "[") {
        return new List(this->getArgs());
    } else if (_currentToken->tokenType() == ',') {
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
    if (term ) {
        args.push_back(term);
    }
    while (!this->createTerm() && _currentToken->tokenValue() == ",") { // null && value is ', '
        args.push_back(this->createTerm());
    }
    return args;
}