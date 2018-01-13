#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "./iterator.h"
class List;
template <class Item>
class ListIterator : public Iterator<Item> {
public:
    ListIterator(List *list): _list(list) {

    }

    Item currentItem() {
        return this->_list->args(this->_index);
    }

    bool isDone() {
        return this->_list->argSize() <= this->_index;
    }
    
    void next() {
        this->_index++;
    }
    
    void first() {
        this->_index = 0;
    }
private:
    List *_list;
    int _index;
};


#endif