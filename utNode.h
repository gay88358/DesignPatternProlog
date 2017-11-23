#ifndef UTNODE_H
#define UTNODE_H
#include <vector>
using std::vector;

#include "./include/node.h"
#include "./include/scanner.h"
#include "./include/term.h"
#include "./include/variable.h"
#include "./include/number.h"
#include "./include/matchExp.h"
#include "./include/andExp.h"
#include "./include/orExp.h"
#include "./include/struct.h"
#include "./include/termExp.h"

TEST(Node, expression1) { // X = 5.
    Variable X("X");
    Number five(5);
    MatchExp m_exp(new TermExp(&X), new TermExp(&five));
    Node *expression =& m_exp;
    ASSERT_EQ(true, expression->evaluate());
}

TEST(Node, expression2) { // X = 5, Y = 6, X = Y.
    Variable X("X");
    Variable Y("Y");
    Number five(5);
    Number six(6);
    MatchExp m_exp1(new TermExp(&X), new TermExp(&five)); // X = 5
    MatchExp m_exp2(new TermExp(&Y), new TermExp(&six)); // Y = 6
    MatchExp m_exp3(new TermExp(&X), new TermExp(&Y)); // X = Y
    AndExp and_exp1(&m_exp1, &m_exp2);
    AndExp and_exp2(&and_exp1, &m_exp3);
    Node *expression =& and_exp2;
    ASSERT_EQ(false, expression->evaluate());
}

TEST(Node, expression3) { // X = 6; X = 5.
    Variable X("X");
    Number five(5);
    Number six(6);
    MatchExp m_exp1(new TermExp(&X), new TermExp(&six)); // X = 6
    MatchExp m_exp2(new TermExp(&X), new TermExp(&five)); // X = 5
    Node *expression = new OrExp(&m_exp1, &m_exp2);
    ASSERT_EQ(true, expression->evaluate());
}

TEST(Node, expression4) { // X = 5, X = 6 ; X = 1. ----> true
    Variable X("X");
    Number five(5);
    Number six(6);
    Number one(1);
    MatchExp m_exp1(new TermExp(&X), new TermExp(&six)); // X = 6
    MatchExp m_exp2(new TermExp(&X), new TermExp( &five)); // X = 5
    MatchExp m_exp3(new TermExp(&X), new TermExp(&one)); // X = 1
    AndExp and_exp1(&m_exp1, &m_exp2);
    OrExp or_exp1(&and_exp1, &m_exp3);
    Node * expression =& or_exp1;
    ASSERT_EQ(true, expression->evaluate());
} 



TEST(Node, expression8) { // X = 1, X = Y.
    Variable X("X");
    Variable Y("Y");
    ASSERT_EQ("X", X.value());
    ASSERT_EQ("Y", Y.value());

    Number one(1);
    MatchExp m_exp1(new TermExp(&X), new TermExp(&one)); // X = 1
    MatchExp m_exp2(new TermExp(&X), new TermExp(&Y)); // X = Y

    AndExp and_exp1(&m_exp1, &m_exp2);
    
    Node *expression =& and_exp1;
    
    ASSERT_EQ(true, expression->evaluate());
    
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
    
    ASSERT_EQ(",", expression->payload);
    
    ASSERT_EQ("=", expression->left->payload);
    ASSERT_EQ("=", expression->right->payload);
}

/*
TEST(Node, expression6) { // X=1; X=2, Y=s(X).
    Variable X("X");
    Variable Y("Y");
    Number one(1);
    Number two(2);

    Struct s(Atom("s"), vector<Term*> { &X });
    
    MatchExp m_exp1(&X, &one); // X=1 
    MatchExp m_exp2(&X, &two); // X=2
    MatchExp m_exp3(&Y, &s); //   Y=s(X)
    AndExp and_exp1(&m_exp2, &m_exp3);

    OrExp or_exp1(&m_exp1, &and_exp1); //  X=1; X=2, Y=s(X).
    Node * expression =& or_exp1;
    ASSERT_EQ(true, expression->evaluate());
}

TEST(Node, expression7) { //X = 5; Y = 6; Y = 7.
    Variable X("X");
    Variable Y("Y");

    Number five(5);
    Number six(6);
    Number seven(7);

    MatchExp m_exp1(&X, &five); // X=5
    MatchExp m_exp2(&Y, &six); // Y=6
    MatchExp m_exp3(&Y, &seven); // Y=7

    OrExp or_exp1(&m_exp1, &m_exp2);
    OrExp or_exp2(&or_exp1, &m_exp3); 
    Node *expression =& or_exp2;
    ASSERT_EQ(true, expression->evaluate());
}


TEST(Node, expression9) { // "X=1, Y=2, Z=3.
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");

    Number one(1);
    Number two(2);
    Number three(3);

    MatchExp m_exp1(&X, &one); // X=1
    MatchExp m_exp2(&Y, &two); // Y=2
    MatchExp m_exp3(&Z, &three); // Z=3
    

    AndExp and_exp1(&m_exp2, &m_exp3);
    AndExp and_exp2(&m_exp1, &and_exp1);

    Node *expression =& and_exp2;
    ASSERT_EQ(true, expression->evaluate());
    ASSERT_EQ(",", expression->payload);
    
    ASSERT_EQ("=", expression->left->payload);
    ASSERT_EQ(",", expression->right->payload);
    ASSERT_EQ("=", expression->right->left->payload);
    ASSERT_EQ("=", expression->right->right->payload);

}


TEST(Node, expression5) { // X= 5; X = 6; X = 7.
    Variable X("X");
    Number five(5);
    Number six(6);
    Number seven(7);
    
    MatchExp m_exp1(new TermExp(&X), new TermExp(&five)); // X = 5
    MatchExp m_exp2(new TermExp(&X), new TermExp( &six)); // X = 6
    MatchExp m_exp3(new TermExp(&X), new TermExp(&seven)); // X = 7

    OrExp or_exp1(&m_exp1, &m_exp2); // X = 5; X = 6
    OrExp or_exp2(&or_exp1, &m_exp3); // (X = 5; X = 6) ; X = 7.
    Node * expression =&or_exp2;
    ASSERT_EQ(true, expression->evaluate());
}

*/
#endif