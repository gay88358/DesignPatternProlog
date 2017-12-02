#ifndef TERM_H
#define TERM_H

#include <string>
#include "./iterator.h"
#include "./nullIterator.h"
//#include "./bfsIterator.h"
#include <vector>
using std::string;
using std::vector;

class Term {
public:
    virtual void clear();
    virtual string symbol() const;    
    virtual string value() const;
    virtual bool match(Term &term);
    virtual string type() const;
    virtual Term* name();
    virtual int argSize() const;
    virtual vector<Term*> args() const;
    virtual Iterator* createIterator();

    virtual Iterator* createDFSIterator();
    virtual Iterator* createBFSIterator();
    
    virtual Term* find(string symbol);
protected:
    string _value;
    string _symbol;
    string _type;
};

#endif