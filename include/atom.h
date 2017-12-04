#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;
#include "./term.h"
class Atom : public Term {
public:
  Atom (string s);
};

#endif
