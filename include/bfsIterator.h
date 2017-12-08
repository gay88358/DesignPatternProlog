#ifndef BFSITERATOR_H
#define BFSITERATOR_H

#include "./iterator.h"
#include <vector>
#include <queue>
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
        Item term = this->_queue.front();
        if (term != NULL) {
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
            this->_isDone = true;
        }
    } 

    void first() {
        vector<Item> args = this->_term->args();
        for (int i = 0; i < args.size(); i++) {
            this->_queue.push(args[i]);
        }
        this->next();
    }

    ~BFSIterator() {
        delete _currentIt;
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