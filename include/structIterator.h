#ifndef STRUCTITERATOR_H
#define STRUCTITERATOR_H

#include "iterator.h"
class Struct;
template<class Item>
class StructIterator : public Iterator<Item> {
public:
    StructIterator(Struct * s): _struct(s) {

    }

    Item currentItem() {
        return this->_struct->args(this->_index);
    }

    bool isDone() {
        return this->_index >= this->_struct->arity();
    }
    
    void next() {
        this->_index++;
    }
    
    void first() {
        this->_index = 0;
    }
    
    ~StructIterator() {

    }
private:
    Struct* _struct;
    int _index;
};

#endif