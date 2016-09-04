#pragma once

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include "Token.h"
#include "Node.h"


class CalcN
{
    public:
        CalcN();
        ~CalcN();

        void operator()(std::istream &in=std::cin,std::ostream &out=std::cout);
        std::string operator()(const std::string &sin);

    protected:
        void run();
        std::unique_ptr<Node> expr(bool b);
        std::unique_ptr<Node> term(bool b);
        std::unique_ptr<Node> prim(bool b);
        double error(const std::string &s);

    private:
        std::unique_ptr<Token_Stream> m_ts;
        std::ostream *m_out;

        std::map<std::string, double> m_table;
};

