#include "../include/flyWeight.h"
#include <iostream>
using std::cout;
using std::endl;

FlyWeight::FlyWeight(): _index(0), _currentTerm(NULL) {
    this->_args.push_back(vector<Term*> { });
}

void FlyWeight::findTerms(Term * t) {
    Term *findTerm = isRepeat(t->symbol());
    if (findTerm == NULL) {
        this->_currentTerm = t;
    } else {
        this->_currentTerm = findTerm;
    }
}

void FlyWeight::addTerms(Term* t) {
    Term *findTerm = isRepeat(t->symbol());
    // check if exists;
    if (findTerm == NULL) {
        this->_args[_index].push_back(t);
        this->_currentTerm = t;
        this->_allArgs.push_back(t);
    } else {
        this->_currentTerm = findTerm;
        this->_allArgs.push_back(findTerm);
    }
}

Term* FlyWeight::getCurrentTerm() {
    return this->_currentTerm;
}

Term* FlyWeight::isRepeat(string symbol) {
    vector<Term*> args = this->_args[_index];
    for (int i = 0; i < args.size(); i++) {
        Term *findTerm = args[i]->find(symbol);
        if (findTerm != NULL) {
            return findTerm;
        }
    }   
    return NULL;
}

void FlyWeight::addIndex() {
    this->_index++;
    this->_args.push_back(vector<Term*> { });
    this->_currentTerm = NULL;
}

vector<Term*> FlyWeight::getargs() {
    return this->_allArgs;
}

void FlyWeight::pushOrNode(Node *node) {
    this->_orStack.push(node);
}

void FlyWeight::pushAndNode(Node *node) {
    this->_andStack.push(node);
}

Node* FlyWeight::getOrNode() {
    Node *node = this->_orStack.top();
    this->_orStack.pop();

    while (!this->_orStack.empty()) {
        node = new OrExp(this->_orStack.top(), node);
        this->_orStack.pop();
    }
    return node;
}

Node* FlyWeight::getAndNode() {
    Node *node = this->_andStack.top();
    this->_andStack.pop();
    while (!this->_andStack.empty()) {
        node = new AndExp(this->_andStack.top(), node);
        this->_andStack.pop();
    }
    return node;
}
