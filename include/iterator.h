#ifndef ITERATOR_H
#define ITERATOR_H

class Term;
class Iterator {
public:
    virtual Term * currentItem() = 0;
    virtual bool isDone();
    virtual void next();
    virtual void first();
private:
};

#endif