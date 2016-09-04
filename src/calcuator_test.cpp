#include "gmock/gmock.h"
#include "calcuator.h"
using namespace ::testing;

class CalcTest:public Test{
public:
    calcuator c;
};

TEST_F(CalcTest, InitClass) {
    calcuator cc;
}

TEST_F(CalcTest, TestOnlyPrint) {
    EXPECT_EQ(c(";"),"");
}

TEST_F(CalcTest, TestOneNumber) {
    EXPECT_EQ(c("123"),"123\n");
}

TEST_F(CalcTest, TestTwoNumber) {
    EXPECT_EQ(c("123;456"),"123\n456\n");
}

TEST_F(CalcTest, TestPlusAndMinus) {
    EXPECT_EQ(c("1+2;5-3"),"3\n2\n");
}

TEST_F(CalcTest, TestPlusWithName) {
    EXPECT_EQ(c("1+pi"),"4.14159\n");
}


TEST_F(CalcTest, TestSaveName) {
    EXPECT_EQ(c("pi;a=3;b=2+2;a+b"),"3.14159\n3\n4\n7\n");
}


TEST_F(CalcTest, TestMul) {
    EXPECT_EQ(c("2*3"),"6\n");
}

TEST_F(CalcTest, TestDiv) {
    EXPECT_EQ(c("48/8"),"6\n");
}

TEST_F(CalcTest, TestDivByZero) {
    EXPECT_EQ(c("48/0"),"divide by zero!");
}

TEST_F(CalcTest, TestNegitation) {
    EXPECT_EQ(c("-48"),"-48\n");
}

TEST_F(CalcTest, TestNegitationWithPlus) {
    EXPECT_EQ(c("-48+10"),"-38\n");
}

TEST_F(CalcTest, TestLpRp) {
    EXPECT_EQ(c("(1+2)"),"3\n");
}

TEST_F(CalcTest, TestLpWithoutRp) {
    EXPECT_EQ(c("(1+2"),"')' expected");
}

TEST_F(CalcTest, TestMoreRp) {
    EXPECT_EQ(c("(4+5))"),"Invaild symbol\n");
}

TEST_F(CalcTest, TestMoreRpFirst) {
    EXPECT_EQ(c(")1+2"),"primary expected");
}

TEST_F(CalcTest, TestFinalTest) {
    EXPECT_EQ(c("a=3;b=8;c=a*b;(c+10)/2*(4-b)*5"),"3\n8\n24\n-340\n");
}

