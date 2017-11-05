#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using std::string;
class Token {
public:
    Token(string value, int type);
    void SetToken(string const &tokenValue,  int const &type);    
    string tokenValue() const;
    int tokenType() const;
private:
    string _tokenValue;
    int _tokenType;
};


#endif