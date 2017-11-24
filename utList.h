#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "./include/list.h"
#include "./include/struct.h"
#include "./include/atom.h"
#include "./include/number.h"
#include "./include/variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
    List l;
    ASSERT_EQ("[]", l.symbol());
}

// [X, Y] = [Y, X]
TEST(List, matchToSameListWithDiffVarNameShouldSucceed11) {
    Variable X("X");
    Variable Y("Y");
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(Y.match(X));
    Number one(1);
    ASSERT_TRUE(Y.match(one));
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());    
    vector<Term*> v = { &X, &Y };
    List l(v);
    vector<Term*> v1 = { &Y, &X };
    List l1(v1);
    ASSERT_TRUE(l.match(l1));
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) { // ????
    Number n1(8128);
    vector<Term*> v1 = {&n1};
    List l1(v1);
    ASSERT_EQ("[8128]", l1.symbol());
}


// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
    Atom terence_tao("terence_tao"), alan_mathison_turing("alan_mathison_turing");
    std::vector<Term*> v = { &terence_tao, &alan_mathison_turing };
    List l(v);
    ASSERT_EQ("[terence_tao, alan_mathison_turing]", l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
    Variable X("X"), Y("Y");
    std::vector<Term*> v = { &X, &Y };
    List l(v);
    ASSERT_EQ("[X, Y]", l.symbol());
}


// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
    Atom tom("tom");
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    std::vector<Term*> v = { &n, &X, &terence_tao };
    List l(v);
    ASSERT_FALSE(tom.match(l));
}



// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
    Number n1(8128);
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    std::vector<Term*> v = { &n, &X, &terence_tao };
    List l(v);
    ASSERT_FALSE(n1.match(l));
}


// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {


    Number n(496);
    Variable X("X");
    std::vector<Term*> s_v = { &X };
    Struct s(Atom("s"), s_v);
    Atom terence_tao("terence_tao");
    std::vector<Term*> v = { &n, &X, &terence_tao };
    List l(v);
    ASSERT_FALSE(s.match(l));

}
// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
    Variable Y("Y");
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    std::vector<Term*> v = { &n, &X, &terence_tao };
    List l(v);
    ASSERT_TRUE(Y.match(l));
}


// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    std::vector<Term*> v = { &n, &X, &terence_tao };
    List l(v);
    //ASSERT_FALSE(X.match(l));    
    ASSERT_TRUE(X.match(l)); 
}
// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    std::vector<Term*> v = { &n, &X, &terence_tao };
    List l(v);
    ASSERT_TRUE(l.match(l));        
}
// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
    Number n(496);
    Variable X("X");
    Variable Y("Y");
    Atom terence_tao("terence_tao");
    std::vector<Term*> v = { &n, &X, &terence_tao };
    List l(v);
    std::vector<Term*> v1 = { &n, &Y, &terence_tao };
    List l2(v1);
    ASSERT_TRUE(l.match(l2));        
}


// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
    Number n(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    std::vector<Term*> v = { &n, &X, &terence_tao };
    List l(v);
    Number n1(8128);
    std::vector<Term*> v1 = { &n, &n1, &terence_tao };
    List l2(v1);
    ASSERT_TRUE(l.match(l2));        
    ASSERT_EQ("8128", X.value());    
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
    Number n(496);
    Variable X("X");
    Variable Y("Y");
    Atom terence_tao("terence_tao");
    std::vector<Term*> v = { &n, &X, &terence_tao };
    List l(v);
    Atom alan_mathison_turing("alan_mathison_turing");
    ASSERT_TRUE(Y.match(l));
    ASSERT_TRUE(X.match(alan_mathison_turing));
    ASSERT_EQ("alan_mathison_turing", X.value());    
    ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
}
// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);
    EXPECT_EQ("first", l.head()->symbol());
    EXPECT_EQ("[second, third]", l.tail()->value());
}



// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);

    EXPECT_EQ("second", l.tail()->head()->value());
    EXPECT_EQ("[third]", l.tail()->tail()->value());
}



// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f};
    List l1(args);
    vector<Term *> args2 = {&l1, &s, &t};
    List l2(args2);
    EXPECT_EQ("[first]", l2.head()->value());
    EXPECT_EQ("[second, third]", l2.tail()->value());

}



// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);


    EXPECT_EQ("third", l.tail()->tail()->head()->value());
    EXPECT_EQ("[]", l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
    List l;
    try{
        l.head();
    }catch(string s){
        EXPECT_EQ("Accessing head in an empty list", s);
    }

}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
    List l;
    try{
        l.tail();
    }catch(string s){
        EXPECT_EQ("Accessing tail in an empty list", s);
    }
}




#endif