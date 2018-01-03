#ifndef ITERATOR_H
#define ITERATOR_H

template<class Item>
class Iterator {
public:
    virtual Item currentItem() = 0;
    virtual bool isDone() {
        return true;
    }
    virtual void next() {

    }
    virtual void first() {

    }
    virtual ~Iterator() {

    }
};
#endif