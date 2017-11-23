#include "../include/parser.h"
#include <iostream>
using std::cout;
using std::endl;
Parser::Parser(Scanner scanner): _scanner(scanner), _builder(new Builder) {
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
        delete atom; // delete memory 
        this->_scanner.nextToken();
        return this->_builder->createStruct(symbol, this->getArgs());
    } else if (_currentToken->tokenType() == _g.NUMBER) {
        return this->_builder->createNumber(stod(_currentToken->tokenValue()));
    } else if (_currentToken->tokenValue() == "[") {
        return this->_builder->createList(this->getArgs());
    } else if (_currentToken->tokenType() == ',') {
        return NULL;
    } else if (_currentToken->tokenType() == ';') {
        return NULL;
    } else if (_currentToken->tokenType() == '.') {
        return NULL;
    }
    else 
        return NULL;
}


Term* Parser::isSameTerm(Term *term) {
    for (int i = 0; i < this->_tempTerms.size(); i++) {
        Term *findTerm = this->_tempTerms[i]->find(term->symbol());
        if (findTerm != NULL) {
            return findTerm;
        }
    }   
    return NULL;
}

vector<Term*> Parser::getArgs() {
    vector<Term*> args;
    Term *term = this->createTerm();
    if (term == NULL)  {
        return args;
    }

    if (term) {
        Term *findTerm = this->isSameTerm(term);
        if (findTerm != NULL) {
            args.push_back(findTerm);
        } else {
            args.push_back(term);
        }  
    }

    while (!this->createTerm() && _currentToken->tokenValue() == ",") { // not null && value is ', '
        Term *t = this->createTerm();
        Term *findTerm = this->isSameTerm(t);
        if (findTerm != NULL) {
            args.push_back(findTerm);
        } else {
            args.push_back(t);
        }
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

void Parser::transFromTempToTerms() {
    for (int i = 0; i < _tempTerms.size(); i++) 
        this->_terms.push_back(_tempTerms[i]);
    this->_tempTerms.clear();
}

void Parser::matchings() {
    stack<Node*> node_stack;
    node_stack.push(this->term());
    
    while (this->_currentToken->tokenValue() == ";") {
        // copy term in the tempterms and insert all terms in the terms
        // clear all temp terms
        this->transFromTempToTerms();
        node_stack.push(this->term());
    }
    
    transFromTempToTerms();
    Node *node = node_stack.top();
    node_stack.pop();
    while (!node_stack.empty()) {
        node = new OrExp(node_stack.top(), node);
        node_stack.pop();
    }
    this->_expTree = node;
}

Node* Parser::factor() {
    Term *left_term = this->createTerm(); // Term::= var|atom|struct|list|num

    Term *findTerm = this->isSameTerm(left_term);
    if (findTerm != NULL) {
        left_term = findTerm;
        this->_tempTerms.push_back(findTerm);
    } else {
        this->_tempTerms.push_back(left_term);
    }

    
    this->createTerm(); // =
    
    Term *right_term = this->createTerm(); // Term::= var|atom|struct|list|num
    findTerm = this->isSameTerm(right_term);
    if (findTerm != NULL) {
        right_term = findTerm;
        this->_tempTerms.push_back(findTerm);
    } else {
        this->_tempTerms.push_back(right_term);
    }
 
    this->createTerm();
    return new MatchExp(new TermExp(left_term), new TermExp(right_term));
}

Node* Parser::term() {
    stack<Node*> node_stack;
    Node* factor = this->factor();

    node_stack.push(factor);
    
    while (this->_currentToken->tokenValue() == ",") {
        node_stack.push(this->factor());
    }
    
    Node *node = node_stack.top();
    node_stack.pop();
    while (!node_stack.empty()) {
        node = new AndExp(node_stack.top(), node);
        node_stack.pop();
    }
    return node;
}

vector<Term *> Parser::getTerms() {
    return this->_terms;
}

Node* Parser::expressionTree() {
    return this->_expTree;
}
