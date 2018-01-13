#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "./listIterator.h"
#include <vector>
using std::vector;

class List : public Term {
public:
  string symbol() const;
  string value() const;
  bool match(Term & term);
  int argSize() const;
  Term* args(int index) const;
  vector<Term*> args() const;
  Term* find(string symbol);
  Iterator<Term*>* createIterator() {
    return new ListIterator<Term*>(this);
  }
public:
  List ();
  List (vector<Term *> const & elements);
  Term * head() const;
  List * tail();
private:
  vector<Term *> _elements;
};

#endif