#pragma once

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include "Token.h"


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
        std::unique_ptr<Token_Stream> m_ts;
        std::ostream *m_out;

        std::map<std::string, double> m_table;
};

