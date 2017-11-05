#include "../include/builder.h"
Builder::Builder() {

}

Term* Builder::getTerm(Token *token) {
    return this->_term;
}

void Builder::buildTerm(Token *token) {
    if (token->tokenType() == _g.VAR) {
        this->_term =  new Variable(token->tokenValue());
    } else if (token->tokenType() == _g.ATOM) {
        this->_term = new Atom(token->tokenValue());        
    } else if (token->tokenType() == _g.NUMBER) {
        this->_term = new Number(stod(token->tokenValue()));        
    } else if (token->tokenType() == (int)',') {
        //this->_term = NULL;
    } else {
        this->_term = NULL;
    }
}

Term* Builder::getTerm() {
    return this->_term;
}





