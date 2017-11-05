#include "../include/token.h"
#include <iostream>

Token::Token(string value, int type):_tokenValue(value), _tokenType(type) {
}

void Token::SetToken(string const &tokenValue, int const &type) {
    this->_tokenValue = tokenValue;
    this->_tokenType = type;
}

int Token::tokenType() const {
    return this->_tokenType;
}

string Token::tokenValue() const {
    return this->_tokenValue;
}
