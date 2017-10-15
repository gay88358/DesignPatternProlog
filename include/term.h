#ifndef TERM_H
#define TERM_H

#include <string>

using std::string;

class Term {
public:
    virtual string symbol() const;    
    virtual string value() const;
    virtual bool match(Term &term);
protected:
    string _value;
    string _symbol;
};

#endif