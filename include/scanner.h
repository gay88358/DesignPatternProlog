#ifndef SCANNER_H
#define SCANNER_H

#include "./global.h"
#include "./token.h"
#include <string>
#include <sstream>
#include <stack>         

using std::string;
using std::stack;

class Scanner {
public:
    Scanner(string buffer = "");
    bool isLegal();
    string buffer() const;
    int position()const;
    int skipLeadingWhiteSpace();
    bool legalPosition();
    char currentChar();
    double extractNumber();
    string extractAtom();
    char extractChar();
    string extractAtomSC();
    string extractVar();
    Token* nextToken();
    bool isStructFormat();
    string extractDotStruct();
private:
    Global _global;
    string _buffer;
    int _position;
};

#endif