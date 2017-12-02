#include "../include/nullIterator.h"

NullIterator::NullIterator(Term* term): _term(term) {

}


Term * NullIterator::currentItem() {
    return this->_term;
}

