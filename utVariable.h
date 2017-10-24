#ifndef UTVARIABLE_H
#define UTVARIABLE_H

#include "./include/variable.h"
#include "./include/number.h"
#include "./include/atom.h"
#include "./include/struct.h"

TEST(Variable, test){
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    
    Number n(1);
    Number n1(5);
    
    ASSERT_TRUE(X.match(n));
    ASSERT_TRUE(X.match(Y));
    ASSERT_FALSE(Y.match(n1));
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
}


TEST(Variable, constructor){
    Variable X("X");
    ASSERT_EQ("X", X.symbol());
}

TEST(Variable , matching){
    Atom tom("tom");
    Variable X("X");
    X.match(tom);
    ASSERT_EQ("tom", X.value());
}

TEST (Variable , haveValue){
    Atom tom("tom");
    Atom jerry("jerry");
    Variable X("X");
    ASSERT_TRUE(X.match(tom));
    ASSERT_FALSE(X.match(jerry));
}
// ?- X=Y, Y=Z, Z=X, Z = 5
// X=Y=Z=5
TEST(Variable, x_y_z_x_match) {
    Variable X("X");  
    Variable Y("Y");  
    Variable Z("Z");  
    Number five(5);
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(Y.match(Z));
    ASSERT_TRUE(Z.match(X));
    ASSERT_TRUE(Z.match(five));
    ASSERT_EQ("5", X.value());

    ASSERT_EQ("5", Y.value());
    ASSERT_EQ("5", Z.value());
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
    Variable X("X");  
    Number n(2.7182);    
    ASSERT_TRUE(X.match(n));
    ASSERT_EQ("2.7182", X.value());
}
// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
    Variable X("X");
    Variable Y("Y");
    Number one(1);
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(X.match(one));
    ASSERT_EQ("1", Y.value());
}
// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
    Variable X("X");
    Variable Y("Y");
    Number one(1);
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(Y.match(one));
    ASSERT_EQ("1", X.value());
}
// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
    Variable X("X");
    Number one(1);
    ASSERT_TRUE(X.match(X));
    ASSERT_TRUE(X.match(one));
    ASSERT_EQ("1", X.value());
}
// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
    Variable Y("Y");
    Number one(1);
    Variable X("X");
    ASSERT_TRUE(Y.match(one));    
    ASSERT_TRUE(X.match(Y));
    ASSERT_EQ("1", X.value());    
}
// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
    Variable Y("Y");
    Number one(1);
    Variable X("X");
    Variable Z("Z");
    ASSERT_TRUE(X.match(Y));
    ASSERT_TRUE(Y.match(Z));
    ASSERT_TRUE(Z.match(one));
    
    ASSERT_EQ("1", X.value());    
    ASSERT_EQ("1", Y.value());    
    ASSERT_EQ("1", Z.value());    
}
// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
    Variable Y("Y");
    Number one(1);
    Variable X("X");
    Variable Z("Z");
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(X.match(Z));
    EXPECT_TRUE(Z.match(one));
    EXPECT_EQ("1", Z.value());    
    
    EXPECT_EQ("1", X.value());    
    EXPECT_EQ("1", Y.value());    

}
// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {
    Variable X("X");
    std::vector<Term*> v = { &X };
    Struct s(Atom("s"), v);
    Variable Y("Y");

    ASSERT_TRUE(Y.match(s));
    ASSERT_EQ("Y", Y.symbol());    
    ASSERT_EQ("s(X)", Y.value());    
    
}
// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
    Variable X("X");
    std::vector<Term*> v = { &X };
    Struct s(Atom("s"), v);
    Variable Y("Y");
    ASSERT_TRUE(Y.match(s));
    Atom teddy("teddy");
    ASSERT_TRUE(X.match(teddy));
    ASSERT_EQ("Y", Y.symbol());    
    ASSERT_EQ("s(teddy)", Y.value());    
}
#endif