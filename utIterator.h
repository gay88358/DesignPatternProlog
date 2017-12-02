#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "./include/iterator.h"
#include "./include/number.h"
#include "./include/variable.h"
#include "./include/nullIterator.h"
#include "./include/atom.h"
#include "./include/struct.h"
#include "./include/dfsIterator.h"
#include "./include/bfsIterator.h"
#include "./include/list.h"
#include <iostream>
using std::cout;
using std::endl;
TEST (Iterator, number_nullIterator) {
    Number one(1);
    Iterator *it = one.createIterator();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

TEST (Iterator, variable_nullIterator) {
    Variable X("X");
    Iterator *it = X.createIterator();
    ASSERT_EQ("X", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

TEST (Iterator, atom_nullIterator) {
    Atom tom("tom");
    Iterator *it = tom.createIterator();
    ASSERT_EQ("tom", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

TEST(Iterator, struct_iterator) {
    // s(X, tom, 1.22)
    Variable X("X");
    Atom tom("tom");
    Number n(1.22);
    Struct s(Atom("s"), { &X, &tom, &n });
    Iterator *it = s.createBFSIterator();
    it->first();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("tom", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("1.22", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(Iterator, complex_struct_iterator) {
    // triangle(point(1, 2), point(2, 3), point(4, 5));
    Number one(11);
    Number two(22);
    Number three(33);
    Number four(44);
    Number five(55);

    Struct p1(Atom("point"), { &one, &two });
    Struct p2(Atom("point"), { &two, &three });
    Struct p3(Atom("point"), { &four, &five });
    Struct t(Atom("triangle"), { &p1, &p2, &p3 });
    ASSERT_EQ("triangle(point(11, 22), point(22, 33), point(44, 55))", t.symbol());
    Iterator *it = t.createBFSIterator();
    it->first(); // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("point(11, 22)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("point(22, 33)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("point(44, 55)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("11", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("22", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("22", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("33", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("44", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("55", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());

}


TEST(BFSIterator, struct_bfs) {
    Variable X("X");
    Number two(2);
    Number three(3);
    
    Struct s(Atom("s"), { &X });
    Struct s1(Atom("s"), { &s, &two, &three });
    Iterator *it = s1.createBFSIterator();
    it->first(); // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("s(X)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(DFSIterator, struct_dfs) {
    Variable X("X");
    Number two(2);
    Number three(3);
    Struct s(Atom("s"), { &X });
    Struct s1(Atom("s"), { &s, &two, &three });
    Iterator *it = s1.createDFSIterator();
    it->first(); // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("s(X)", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next();
    
    ASSERT_TRUE(it->isDone());
}

TEST(BFSIterator, simple_list_iterator) {
    // [496, X, terence_tao]
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    List l({ &n, &X, &terence_tao });
    Iterator *it = l.createDFSIterator();
    
    it->first(); // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("496", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("terence_tao", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(BFSIterator, complex_list_bfsiterator) {
    // [[496, X, terence_tao], tom, jerry]
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    List l({ &n, &X, &terence_tao });
    Atom tom("tom");
    Atom jerry("jerry");
    List l2({ &l, &tom, &jerry });
    
    Iterator *it = l2.createBFSIterator();
    
    it->first(); // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("tom", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("jerry", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("496", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("terence_tao", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(DFSIterator, complex_list_dfsiterator) {
    // [[496, X, terence_tao], tom, jerry]
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    List l({ &n, &X, &terence_tao });
    Atom tom("tom");
    Atom jerry("jerry");
    List l2({ &l, &tom, &jerry });
    
    Iterator *it = l2.createDFSIterator();
    
    it->first(); // initialize

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("496", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("terence_tao", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("tom", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("jerry", it->currentItem()->symbol());
    it->next();

    ASSERT_TRUE(it->isDone());
}

TEST(BFSIterator, complex_list_bfsiterator2) {
    // [[[496, X, terence_tao], tom, jerry], s(X, Y, [1, 2]), tom]
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    List l({ &n, &X, &terence_tao });

    Atom tom("tom");
    Variable Y("Y");
    Number one(1);
    Number two(2);
    List l3({ &one, &two });
    Struct s(Atom("s"), { &X, &Y, &l3 });
    List l4({ &l, &s, &tom });
    ASSERT_EQ("[[496, X, terence_tao], s(X, Y, [1, 2]), tom]", l4.symbol());

    Iterator *it = l4.createBFSIterator();
    it->first(); // initialize
    
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("s(X, Y, [1, 2])", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("tom", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("496", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("terence_tao", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[1, 2]", it->currentItem()->symbol());
    it->next();

    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();    ASSERT_FALSE(it->isDone());
    
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(DFSIterator, complext_list_dfsiterator2) {
    // [[[496, X, terence_tao], tom, jerry], s(X, Y, [1, 2]), tom]
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    List l({ &n, &X, &terence_tao });

    Atom tom("tom");
    Variable Y("Y");
    Number one(1);
    Number two(2);
    List l3({ &one, &two });
    Struct s(Atom("s"), { &X, &Y, &l3 });
    List l4({ &l, &s, &tom });
    ASSERT_EQ("[[496, X, terence_tao], s(X, Y, [1, 2]), tom]", l4.symbol());

    Iterator *it = l4.createDFSIterator();
    it->first(); // initialize
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[496, X, terence_tao]", it->currentItem()->symbol());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("496", it->currentItem()->symbol());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("terence_tao", it->currentItem()->symbol());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("s(X, Y, [1, 2])", it->currentItem()->symbol());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("X", it->currentItem()->symbol());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("Y", it->currentItem()->symbol());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("[1, 2]", it->currentItem()->symbol());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("1", it->currentItem()->symbol());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("2", it->currentItem()->symbol());
    
    it->next(); 
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("tom", it->currentItem()->symbol());
    
    it->next();
    ASSERT_TRUE(it->isDone());
}
#endif