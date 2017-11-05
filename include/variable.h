#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "./term.h"
using std::string;
using std::vector;

class Variable : public Term {
public:
    Variable(string s);
    string value() const;
    bool match(Term &term);
    bool isRepeat(vector<Term*>);
private:
    string head;
    vector<Term*> _path;
    Term * _instance = NULL;
};

#endif
