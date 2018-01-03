#ifndef LIST_H
#define LIST_H

#include "term.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  string symbol() const;
  string value() const;
  bool match(Term & term);
  int argSize() const;
  vector<Term*> args() const;
  Term* find(string symbol);
public:
  List ();
  List (vector<Term *> const & elements);
  Term * head() const;
  List * tail();
private:
  vector<Term *> _elements;
};

#endif