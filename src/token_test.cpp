#include "gmock/gmock.h"
#include "Token.h"

TEST(TokenTest, InitClass) {
    Token_Stream t(std::cin);
    EXPECT_EQ(t.current().kind,Kind::end);
}

TEST(TokenTest, TestKindEnd) {
    Token_Stream t("");
    EXPECT_EQ(t.get().kind,Kind::end);
}

TEST(TokenTest, TestKindPrint) {
    Token_Stream t(";");
    EXPECT_EQ(t.get().kind,Kind::print);
}

TEST(TokenTest, TestKindNumber) {
    Token_Stream t("123");
    EXPECT_EQ(t.get().kind,Kind::number);
    EXPECT_DOUBLE_EQ(t.current().number_value,123);
}

TEST(TokenTest, TestKindPointNumber) {
    Token_Stream t(".123");
    EXPECT_EQ(t.get().kind,Kind::number);
    EXPECT_DOUBLE_EQ(t.current().number_value,.123);
}

TEST(TokenTest, TestKindName) {
    Token_Stream t("abc");
    EXPECT_EQ(t.get().kind,Kind::name);
    EXPECT_EQ(t.current().string_value,"abc");
}

TEST(TokenTest, TestKindNameWithAssigne) {
    Token_Stream t("abc=");
    EXPECT_EQ(t.get().kind,Kind::name);
    EXPECT_EQ(t.current().string_value,"abc");
    EXPECT_EQ(t.get().kind,Kind::assign);
}

TEST(TokenTest, TestSpaceAndCarryInLine) {
    Token_Stream t("  abc  =");
    EXPECT_EQ(t.get().kind,Kind::name);
    EXPECT_EQ(t.current().string_value,"abc");
    EXPECT_EQ(t.get().kind,Kind::assign);
}

TEST(TokenTest, TestCarriageReturnInLine) {
    Token_Stream t("\n  abc\n  =");
    EXPECT_EQ(t.get().kind,Kind::print);
    EXPECT_EQ(t.get().kind,Kind::name);
    EXPECT_EQ(t.current().string_value,"abc");
    EXPECT_EQ(t.get().kind,Kind::print);
}


