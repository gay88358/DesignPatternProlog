#include "../include/scanner.h"
#include <iostream>
//#include "../include/global.h"

Scanner::Scanner(string buffer): _buffer(buffer), _position(0) {

}

string Scanner::buffer() const {
    return this->_buffer;
}

int Scanner::position() const {
    return this->_position;
}

bool Scanner::legalPosition() {
    return this->_position < this->_buffer.length();
}

int Scanner::skipLeadingWhiteSpace() {
    while(this->_buffer[this->_position] == ' ' && this->legalPosition()) {
        this->_position++;
    }
    return this->_position;
}

char Scanner::currentChar() {
    return this->_buffer[this->_position];
}

double Scanner::extractNumber() { // still can not prevent input from ilegal format
    // prevent extract term is not number
    // if (!isdigit(currentChar())) return -999.9;
    int begin = this->position();
    while(isdigit(currentChar()) || currentChar() == '.') {
        this->_position++;
    }
    return stod(this->_buffer.substr(begin, this->_position - begin));
}

char Scanner::extractChar() {
    return this->_buffer[this->_position++];
}

string Scanner::extractVar() {
    int begin = this->position();
    while(isalnum(currentChar()) || currentChar() == '_') {
        this->_position++;        
    }
    return this->_buffer.substr(begin, this->_position - begin);
}

string Scanner::extractAtom() {
    int begin = this->position();
    while(isalnum(currentChar())) {
        this->_position++;        
    }
    return this->_buffer.substr(begin, this->_position - begin);
}

string Scanner::extractAtomSC() {
    int begin = this->position();
    while(_global.isSpecialCh(currentChar())) {
        this->_position++;        
    }
    return this->_buffer.substr(begin, this->_position - begin);
}

bool Scanner::isLegal() {
    stack<char> s;
    for (int i = 0; i < this->_buffer.length(); i++) {
        if (_global.isFormerPart(this->_buffer[i])) { // left push
            s.push(this->_buffer[i]);
        }
        if (_global.isLatterPart(this->_buffer[i])) { // right pop
            if (_global.misMatch(s.top(), this->_buffer[i])) { // ismatch()
                return false;
            } else {
                s.pop();
            }
        }   
    }
    return true;
}

bool Scanner::isStructFormat() {
    int index = this->position();
    while (this->_buffer[index++] == '.' && index <= this->_buffer.length()) {
        if (this->_buffer[index] == '(')
            return true;
    }
    return false;
}

string Scanner::extractDotStruct() {
    int begin = this->position();
    while(currentChar() == '.') {
        this->_position++;        
    }
    return this->_buffer.substr(begin, this->_position - begin);
}

Token* Scanner::nextToken() {
    if (skipLeadingWhiteSpace() >= this->_buffer.length()) {
        return new Token("EOS", _global.EOS);        
    } else if (currentChar() == '.' && isStructFormat()) {
        return new Token(extractDotStruct(), _global.ATOM);                
    } else if (currentChar() == '=' || currentChar() == ',' || currentChar() == '.' || currentChar() == '(' || currentChar() == ')' || currentChar() == '[' || currentChar() == ']') {
        char token = extractChar();
        int type = token;
        string value;
        value.push_back(token);
        return new Token(value, type);                     
    } else if (isdigit(currentChar())) {
        std::stringstream ss;
        ss << extractNumber();        
        return new Token(ss.str(), _global.NUMBER);
    } else if (islower(currentChar())) {
        return new Token(extractAtom(), _global.ATOM);                
    } else if (isupper(currentChar()) || currentChar() == '_') {
        return new Token(extractVar(), _global.VAR);             
    } else if (_global.isSpecialCh(currentChar())) {
        return new Token(extractAtomSC(), _global.ATOMSC);             
    } 
    return 0;
}



