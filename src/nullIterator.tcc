#include "../include/nullIterator.h"
template<class Item>
NullIterator<Item>::NullIterator(Item term): _term(term) {

}

template<class Item>
Item NullIterator<Item>::currentItem() {
    return this->_term;
}

