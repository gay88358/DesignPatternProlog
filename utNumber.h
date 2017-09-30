#ifndef UTNUMBER_H
#define UTNUMBER_H
#include "number.h"

TEST(Number, first) {
    Number one("1");
    ASSERT_EQ(one.symbol(), "1");
}

#endif