#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#include <vector>
#include <stack>         
#include "./term.h"
#include "./node.h"
#include "./orExp.h"
#include "./andExp.h"
using std::stack;

using std::vector;

class FlyWeight {
public:
    FlyWeight();
    void addTerms(Term* t);
    void addIndex();
    Term* isRepeat(string symbol);
    Term* getCurrentTerm();
    vector<Term*> getargs();
    void pushOrNode(Node *node);
    void pushAndNode(Node *node);
    void findTerms(Term *);
    Node* getOrNode();
    Node* getAndNode();
private:
    vector<vector<Term*>> _args;
    vector<Term*> _allArgs;
    int _index;
    Term* _currentTerm;
    stack<Node*> _andStack;
    stack<Node*> _orStack;

};

#endif