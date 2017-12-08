#ifndef BFSITERATOR_H
#define BFSITERATOR_H

#include "./iterator.h"
#include <vector>
#include <queue>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
using std::queue;
template <class Item>
class BFSIterator : public Iterator<Item> {
public:
    /*BFSIterator(Item);
    Item currentItem();
    bool isDone();
    void next();
    void first();
    ~BFSIterator();*/
    BFSIterator(Item t): _term(t) {
        this->_isDone = false;
    }

    Item currentItem() {
        return this->_currentTerm;
    }

    bool isDone() {
        return this->_isDone;
    }

    void next() {
        Item term;
        if (!this->_queue.empty()) {
            term = this->_queue.front();
            cout << term->symbol() << endl;
        } else {
            cout << "nullptr" << endl;
            term = nullptr;
        }

        if (term != nullptr) {
            cout << "in next" << endl;
            this->_currentTerm = term;
            this->_queue.pop();
            vector<Item> args = term->args();
            if (args.size() > 0)
            {
                for (int i = 0; i < args.size(); i++) {
                    this->_queue.push(args[i]);
                }
            }
        } else {
            cout << "isDonw" << endl;

            this->_isDone = true;
        }
    } 

    void first() {
        vector<Item> args = this->_term->args();
        cout << args.size() << endl;
        for (int i = 0; i < args.size(); i++) {
            this->_queue.push(args[i]);
        }
        this->next();
    }

    ~BFSIterator() {
        //std::cout << "bfsIterator delete" << std::endl;
    }

private:
    Item _term;
    Iterator<Item> *_currentIt;
    queue<Item> _queue;
    Item _currentTerm;
    bool _isDone;
};
//#include "../src/bfsIterator.tcc"

#endif