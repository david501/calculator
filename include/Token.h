#pragma once

#include <istream>
#include <sstream>
#include <string>
#include <stdexcept>

enum class Kind:char{
    name,number,end,
    plus='+',minus='-',mul='*',div='/',assign='=',lp='(',rp=')',
    print=';', power
};

struct Token
{
    Kind kind;
    std::string string_value;
    double number_value;
};

class Token_Stream{
public:
    Token_Stream(std::istream &in);
    Token_Stream(const std::string s);
    ~Token_Stream();

    Token get();
    const Token& current()const {return m_cur;};

private:
    Token m_cur{Kind::end};
    std::istringstream m_iss;
    std::istream *m_is;
};


