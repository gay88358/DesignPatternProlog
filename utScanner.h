#ifndef UTSCANNER_H
#define UTSCANNER_H

#include "../include/scanner.h"
#include "../include/global.h"

TEST(Scanner, read_string) {
    Scanner scanner("X = 5");
    EXPECT_EQ("X = 5", scanner.buffer());
}

TEST(Scanner, skip_leading_whiteSpace) {
    //               0123456
    Scanner scanner("       12345,  tom,   Date");
    EXPECT_EQ(0, scanner.position());
    EXPECT_EQ(7, scanner.skipLeadingWhiteSpace());
}

TEST(Scanner, extract_char) {
    //               0123456
    Scanner scanner("     , tom");
    EXPECT_EQ(5, scanner.skipLeadingWhiteSpace());
    EXPECT_EQ(',', scanner.extractChar());
    EXPECT_EQ(6, scanner.position());
}

TEST(Scanner, extract_numer) {
    //               0123456789012
    Scanner scanner("       12345,  tom,   Date");
    EXPECT_EQ(7, scanner.skipLeadingWhiteSpace());
    EXPECT_EQ(12345, scanner.extractNumber());
    EXPECT_EQ(12, scanner.position());
}

TEST(Scanner, extract_float_number) {
    //               012345678901
    Scanner scanner("  12345.123,  tom,   Date");
    EXPECT_EQ(2, scanner.skipLeadingWhiteSpace());
    EXPECT_EQ(12345.123, scanner.extractNumber());
    EXPECT_EQ(11, scanner.position());
}

TEST(Scanner, extract_atom) {
    //               0123456
    Scanner scanner("  tom,   Date");
    EXPECT_EQ(2, scanner.skipLeadingWhiteSpace());
    EXPECT_EQ("tom", scanner.extractAtom());
    EXPECT_EQ(5, scanner.position());
}

TEST(Scanner, extract_var) {
    //               0123456789
    Scanner scanner("  tom,   Date");
    EXPECT_EQ(2, scanner.skipLeadingWhiteSpace());
    EXPECT_EQ("tom", scanner.extractAtom());
    EXPECT_EQ(5, scanner.position());
    EXPECT_EQ(',', scanner.extractChar());
    EXPECT_EQ(6, scanner.position());
    EXPECT_EQ(9, scanner.skipLeadingWhiteSpace());
    EXPECT_EQ("Date", scanner.extractVar());
}


TEST(Scanner, extract_other_token) {
    //               0123456789012345678901
    Scanner scanner(" =    ,  .");
    EXPECT_EQ(0, scanner.position());
    Token *token = scanner.nextToken();
    EXPECT_EQ("=", token->tokenValue());
    int type = '=';
    EXPECT_EQ(type, token->tokenType());
    
    token = scanner.nextToken();
    EXPECT_EQ(",", token->tokenValue());
    type = (int)',';
    EXPECT_EQ(type, token->tokenType());
    
    token = scanner.nextToken();
    
    EXPECT_EQ(".", token->tokenValue());
    type = (int)'.';
    EXPECT_EQ(type, token->tokenType());
}

TEST(Scanner, extract_two_term) {
    Scanner scanner("12345,  tom");
    EXPECT_EQ("12345", scanner.nextToken()->tokenValue());
    EXPECT_EQ(",", scanner.nextToken()->tokenValue());
    EXPECT_EQ("tom", scanner.nextToken()->tokenValue());
    
}

TEST(Scanner, illegal_1) {
    Scanner scanner("((])");
    ASSERT_FALSE(scanner.isLegal());
}

TEST(Scanner, illegal_2) {
    Scanner scanner("[1,2)");
    ASSERT_FALSE(scanner.isLegal());
}

TEST(Scanner, illegal_3) {
    Scanner scanner("[(((1, 2)))]");
    ASSERT_TRUE(scanner.isLegal());
}

TEST(Scanner, multiple_scan) {
    Scanner scanner(" 12345,  tom,   Date");
    Token *token = scanner.nextToken();
    EXPECT_EQ("12345", token->tokenValue());

    token = scanner.nextToken();
    EXPECT_EQ(",", token->tokenValue());
    
    token = scanner.nextToken();
    EXPECT_EQ("tom", token->tokenValue());
    
    token = scanner.nextToken();
    EXPECT_EQ(",", token->tokenValue());
    
    token = scanner.nextToken();
    EXPECT_EQ("Date", token->tokenValue());
    
}




TEST(Scanner, token) {
    Global g;
    Scanner scanner("X = 5.");
    EXPECT_EQ("X", scanner.nextToken()->tokenValue());
    EXPECT_EQ("=", scanner.nextToken()->tokenValue());
    EXPECT_EQ("5", scanner.nextToken()->tokenValue());
    EXPECT_EQ(".", scanner.nextToken()->tokenValue());

}

/*
TEST(Scanner, nextTokenChar) {
    //---------------01234
    Global g;
    Scanner scanner("   (");
    int token = scanner.nextToken();
    EXPECT_EQ('(', token);
    EXPECT_EQ(4, scanner.position());    
    token = scanner.nextToken();
    EXPECT_EQ(g.EOS, token);
    EXPECT_EQ(4, scanner.position());
}

TEST(Scanner, nextToken) {
    Global g;
    //               0123
    Scanner scanner("    ");
    EXPECT_EQ(0, scanner.position());
    int token = scanner.nextToken();
    EXPECT_EQ(g.EOS, token);
    //EXPECT_EQ(g.NONE, scanner.tokenValue());
}

TEST(Scanner, nextTokenAtom) {
    //---------------0123
    Global g;
    Scanner scanner("tom");
    EXPECT_EQ(0, scanner.position());
    int token = scanner.nextToken();
    EXPECT_EQ(g.ATOM, token);
    EXPECT_EQ("tom", scanner.tokenValue());
    EXPECT_EQ(3, scanner.position());
}

TEST(Scanner, nextTokenVar) {
    //---------------01234
    Global g;
    Scanner scanner("Date");
    EXPECT_EQ(0, scanner.position());
    int token = scanner.nextToken();
    EXPECT_EQ(g.VAR, token);
    EXPECT_EQ("Date", scanner.tokenValue());
    EXPECT_EQ(4, scanner.position());
}

TEST(Scanner, nextTokenAtomSC) {
    //---------------01234567-890
    Global g;
    Scanner scanner(".*-><&$@\\?");
    EXPECT_EQ(0, scanner.position());
    int token = scanner.nextToken();
    EXPECT_EQ(g.ATOMSC, token);
    EXPECT_EQ(".*-><&$@\\?", scanner.tokenValue());
    EXPECT_EQ(10, scanner.position());
    //EXPECT_EQ(".*-><&$@\\?", symtable[0].first);
    //EXPECT_EQ(ATOMSC, symtable[0].second);
}
*/
  
#endif