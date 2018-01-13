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
    MatchExp m_exp(&X, &five);
    Node *expression =& m_exp;
    ASSERT_EQ(true, expression->evaluate());
}

TEST(Node, expression2) { // X = 5, Y = 6, X = Y.
    Variable X("X");
    Variable Y("Y");
    Number five(5);
    Number six(6);
    MatchExp m_exp1(&X, &five); // X = 5
    MatchExp m_exp2(&Y, &six); // Y = 6
    MatchExp m_exp3(&X, &Y); // X = Y
    AndExp and_exp1(&m_exp1, &m_exp2);
    AndExp and_exp2(&and_exp1, &m_exp3);
    Node *expression =& and_exp2;
    ASSERT_EQ(false, expression->evaluate());
}

TEST(Node, expression3) { // X = 6; X = 5.
    Variable X("X");
    Number five(5);
    Number six(6);
    MatchExp m_exp1(&X,  &six); // X = 6
    MatchExp m_exp2(&X,  &five); // X = 5
    Node *expression = new OrExp(&m_exp1, &m_exp2);
    ASSERT_EQ(true, expression->evaluate());
}

TEST(Node, expression8) { // X = 1, X = Y.
    Variable X("X");
    Variable Y("Y");
    ASSERT_EQ("X", X.value());
    ASSERT_EQ("Y", Y.value());

    Number one(1);
    MatchExp m_exp1(&X,  &one); // X = 1
    MatchExp m_exp2(&X,  &Y); // X = Y

    AndExp and_exp1(&m_exp1, &m_exp2);
    
    Node *expression =& and_exp1;
    
    ASSERT_EQ(true, expression->evaluate());
    
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
    
    ASSERT_EQ(",", expression->payload);
    
    ASSERT_EQ("=", expression->left->payload);
    ASSERT_EQ("=", expression->right->payload);
}

#endif