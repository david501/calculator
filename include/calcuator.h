#pragma once

#include <string>
#include <map>
#include <iostream>
#include "Token.h"

class calcuator
{
    public:
        calcuator(std::istream &in=std::cin,std::ostream &out=std::cout);
        calcuator(const std::string &sin,std::ostream &out=std::cout);
        ~calcuator();

    protected:
        void run();
        double expr(bool b);

    private:
        Token_Stream m_ts;
        std::ostream &m_out;

        std::map<std::string, double> m_table;
};

