#pragma once

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include "Token.h"

class Node{
    Kind kind;
    double number;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
public:
    Node(const Kind k,std::shared_ptr<Node> l,std::shared_ptr<Node> r):kind(k),left(l),right(r){};
    Node(const Kind k,std::shared_ptr<Node> l):kind(k),left(l),right(nullptr){};
    Node(const Kind k,const double d):kind(k),number(d),left(nullptr),right(nullptr){};
    ~Node(){};
    double value(void) const ;
};


class CalcN
{
    public:
        CalcN();
        ~CalcN();

        void operator()(std::istream &in=std::cin,std::ostream &out=std::cout);
        std::string operator()(const std::string &sin);

    protected:
        void run();
        std::shared_ptr<Node> expr(bool b);
        std::shared_ptr<Node> term(bool b);
        std::shared_ptr<Node> prim(bool b);
        double error(const std::string &s);

    private:
        std::unique_ptr<Token_Stream> m_ts;
        std::ostream *m_out;

        std::map<std::string, double> m_table;
};

