#include <iostream>
using std::cout;
using std::endl;
template<class Item>
bool Iterator<Item>::isDone() {
    return true;
}

template<class Item>
void Iterator<Item>::next() {

}

template<class Item>
void Iterator<Item>::first() {

}

template<class Item>
Iterator<Item>::~Iterator() {
    cout << "iterator delete" << endl;
}


