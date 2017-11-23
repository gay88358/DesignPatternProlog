#ifndef UTSTRUCT_H
#define UTSTRUCT_H

#include <iostream>
#include <vector>
#include "./include/atom.h"
#include "./include/struct.h"
#include "./include/variable.h"
#include "./include/number.h"


TEST(Struct, struct_match_to_variable) {
    Variable X("X");
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    ASSERT_TRUE(hobby.match(X));
    ASSERT_TRUE(X.match(hobby));
    ASSERT_FALSE(X.match(tom));
}

TEST(Struct, hobby)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    ASSERT_EQ("hobby", hobby.name()->symbol());
    ASSERT_EQ("tom", hobby.args(0)->symbol());
    ASSERT_EQ("chaseMouse", hobby.args(1)->symbol());
}

TEST(Struct, symbol)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    ASSERT_EQ("hobby(tom, chaseMouse)", hobby.symbol());
}

TEST(Struct, match_functor_diff)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    Struct hobby2(Atom("hobby2"), v);
    ASSERT_FALSE(hobby.match(hobby2));  
}



TEST(Struct, match_args_size_diff){
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    std::vector<Term *> v = {&tom, &chaseMouse};
    std::vector<Term *> v1 = {&tom};    
    Struct hobby(Atom("hobby"), v);
    Struct hobby2(Atom("hobby"), v1);
    ASSERT_FALSE(hobby.match(hobby2));  
}



TEST(Struct, match_args_symbol_diff){
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = { &tom, &chaseMouse };
  std::vector<Term *> v1 = { &chaseMouse, &tom };
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby"), v1);
  ASSERT_FALSE(hobby.match(hobby2));    
}

TEST(Struct, match_symbol_same)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    std::vector<Term *> v = { &tom, &chaseMouse };
    Struct hobby(Atom("hobby"), v);
    Struct hobby2(Atom("hobby"), v);
    ASSERT_TRUE(hobby.match(hobby2)); 
}

TEST(Struct, match_atom)
{
  Atom tom("tom");
  std::vector<Term*> v = { &tom };
  Struct hobby(Atom("hobby"), v);
  ASSERT_FALSE(hobby.match(tom));
}

// When Struct s contains a Variable X
// Then #symbol() should return "s(X)"
// and #value() should also return "s(X)"
TEST(Struct, var)
{
    Variable X("X");
    std::vector<Term*> v = { &X };
    Struct s(Atom("s"), v);
    ASSERT_EQ("s(X)", s.symbol());
    ASSERT_EQ("s(X)", s.value());
}



// Given there is Struct s contains a Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() should return "s(X)"
// and #value() should also return "s(tom)"
TEST(Struct, var_match_atom)
{
    Variable X("X");
    std::vector<Term*> v = { &X };
    Struct s(Atom("s"), v);
    Atom tom("tom");
    ASSERT_TRUE(X.match(tom));
    ASSERT_EQ("s(X)", s.symbol());
    ASSERT_EQ("s(tom)", s.value());
}



// Given there are Struct s1 and Struct s2
// When Struct s1 contains Struct s2
// And Struct s2 contains a Variable X
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should also return "s1(s2(X))"
TEST(Struct, nested_struct1)
{
    Variable X("X");
    std::vector<Term*> v = { &X };
    Struct s2(Atom("s2"), v);
    std::vector<Term*> v1 = { &s2 };
    Struct s1(Atom("s1"), v1);
    ASSERT_EQ("s1(s2(X))", s1.symbol());
    ASSERT_EQ("s1(s2(X))", s1.value());
    
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(tom))"
TEST(Struct, nested_struct2)
{
    Variable X("X");
    std::vector<Term*> v = { &X };
    Struct s2(Atom("s2"), v);
    std::vector<Term*> v1 = { &s2 };
    Struct s1(Atom("s1"), v1);
    Atom tom("tom");
    ASSERT_TRUE(X.match(tom));
    ASSERT_EQ("s1(s2(X))", s1.symbol());
    ASSERT_EQ("s1(s2(tom))", s1.value());
}



// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Number pi: 3.14
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(3.14))"
TEST(Struct, nested_struct3)
{
    Variable X("X");
    std::vector<Term*> v = { &X };
    Struct s2(Atom("s2"), v);
    std::vector<Term*> v1 = { &s2 };
    Struct s1(Atom("s1"), v1);
    Number n(3.14);
    ASSERT_TRUE(X.match(n));
    ASSERT_EQ("s1(s2(X))", s1.symbol());
    ASSERT_EQ("s1(s2(3.14))", s1.value());

}



// Given there are Struct s1 contains Struct s2 and Variable X
// And Struct s2 contains Variable Y
// When Variable X matches Variable Y
// And Variable X matches Atom "kent_beck"
// Then #symbol() of s1 should return "s1(s2(Y), X)"
// and #value() of s1 should return "s1(s2(kent_beck), kent_beck)"
TEST(Struct, nested_struct_and_multiVariable)
{
    Variable X("X");
    Variable Y("Y");
    std::vector<Term*> v = { &Y };    
    Struct s2(Atom("s2"), v);
    std::vector<Term*> v1 = { &s2, &X };
    Struct s1(Atom("s1"), v1);
    Atom kent_beck("kent_beck");
    X.match(Y);
    X.match(kent_beck);
    ASSERT_EQ("s1(s2(Y), X)", s1.symbol());
    ASSERT_EQ("s1(s2(kent_beck), kent_beck)", s1.value());

}

TEST(Struct, find_var_in_struct) { // s(s(X)), find X
    Variable X("X");
    Struct s(Atom("s"), vector<Term*> { &X }); // s(X)
    Struct s1(Atom("s"), vector<Term*> { &s }); // s(s(X))
    ASSERT_TRUE(s1.find("X"));
    Struct s2(Atom("s"), vector<Term*> { &s1 });
    ASSERT_TRUE(s2.find("X"));
    ASSERT_FALSE(s2.find("Y"));
}

#endif