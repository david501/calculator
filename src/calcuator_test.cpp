#include "gmock/gmock.h"
#include "calcuator.h"
using namespace std;

TEST(CalcTest, InitClass) {
    calcuator c();
}

TEST(CalcTest, TestOnlyPrint) {
    ostringstream s;
    calcuator c(";",s);
    EXPECT_EQ(s.str(),"");
}

TEST(CalcTest, TestOneNumber) {
    ostringstream s;
    calcuator c("123",s);
    EXPECT_EQ(s.str(),"123\n");
}

TEST(CalcTest, TestTwoNumber) {
    ostringstream s;
    calcuator c("123;456",s);
    EXPECT_EQ(s.str(),"123\n456\n");
}

TEST(CalcTest, TestPlusAndMinus) {
    ostringstream s;
    calcuator c("1+2;5-3",s);
    EXPECT_EQ(s.str(),"3\n2\n");
}

TEST(CalcTest, TestPlusWithName) {
    ostringstream s;
    calcuator c("1+pi",s);
    EXPECT_EQ(s.str(),"4.14159\n");
}


TEST(CalcTest, TestSaveName) {
    ostringstream s;
    calcuator c("pi;a=3;b=2+2;a+b",s);
    EXPECT_EQ(s.str(),"3.14159\n3\n4\n7\n");
}


TEST(CalcTest, TestMul) {
    ostringstream s;
    calcuator c("2*3",s);
    EXPECT_EQ(s.str(),"6\n");
}

TEST(CalcTest, TestDiv) {
    ostringstream s;
    calcuator c("48/8",s);
    EXPECT_EQ(s.str(),"6\n");
}

TEST(CalcTest, TestDivByZero) {
    ostringstream s;
    calcuator c("48/0",s);
    EXPECT_EQ(s.str(),"divide by zero!");
}

TEST(CalcTest, TestNegitation) {
    ostringstream s;
    calcuator c("-48",s);
    EXPECT_EQ(s.str(),"-48\n");
}

TEST(CalcTest, TestNegitationWithPlus) {
    ostringstream s;
    calcuator c("-48+10",s);
    EXPECT_EQ(s.str(),"-38\n");
}

TEST(CalcTest, TestLpRp) {
    ostringstream s;
    calcuator c("(1+2)",s);
    EXPECT_EQ(s.str(),"3\n");
}

TEST(CalcTest, TestLpWithoutRp) {
    ostringstream s;
    calcuator c("(1+2",s);
    EXPECT_EQ(s.str(),"')' expected");
}

TEST(CalcTest, TestMoreRp) {
    ostringstream s;
    calcuator c("(4+5))",s);
    EXPECT_EQ(s.str(),"Invaild symbol\n");
}

TEST(CalcTest, TestMoreRpFirst) {
    ostringstream s;
    calcuator c(")1+2",s);
    EXPECT_EQ(s.str(),"primary expected");
}

TEST(CalcTest, TestFinalTest) {
    ostringstream s;
    calcuator c("a=3;b=8;c=a*b;(c+10)/2*(4-b)*5",s);
    EXPECT_EQ(s.str(),"3\n8\n24\n-340\n");
}

