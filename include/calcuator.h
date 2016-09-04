#pragma once

#include <string>
#include <map>
#include <iostream>
#include "Token.h"

struct calcuator_error
{
    std::string m_s;
    calcuator_error(const std::string &s):m_s(s){};
    std::string& what(){ return m_s;}
};

class calcuator
{
    public:
        calcuator();
        ~calcuator();

        void operator()(std::istream &in=std::cin,std::ostream &out=std::cout);
        std::string operator()(const std::string &sin);

    protected:
        void run();
        double expr(bool b);
        double term(bool b);
        double prim(bool b);
        double error(const std::string &s);

    private:
        Token_Stream *m_ts;
        std::ostream *m_out;

        std::map<std::string, double> m_table;
};

