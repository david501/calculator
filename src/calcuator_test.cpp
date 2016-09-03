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

TEST(CalcTest, TestNumberAndName) {
    ostringstream s;
    calcuator c("123;abc",s);
    EXPECT_EQ(s.str(),"123\n0\n");
}
