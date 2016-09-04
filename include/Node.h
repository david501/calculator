#pragma once

#include <iostream>
#include <memory>
#include <map>
#include "Token.h"

enum class FKind:char {nofunc,sin,cos,tan};
FKind get_FKind(std::string s);

class Node
{
    public:
        Node();
        virtual ~Node();
        virtual double value(void) const=0;
        virtual void print(std::ostream &out=std::cout) const {};

        Node(const Node&n)=delete;
        void operator=(const Node& n)=delete;
    protected:
    private:
};

class NumberNode:public Node{
    double m_number;
public:
    NumberNode(const double d):m_number(d){};
    ~NumberNode(){};
    double value(void) const { return m_number;}
    void print(std::ostream &out=std::cout) const;
};

class UnaryNode:public Node{
    Kind m_kind;
    std::unique_ptr<Node> m_right;
public:
    UnaryNode(const Kind k,std::unique_ptr<Node> &&l):m_kind(k),m_right(std::move(l)){};
    ~UnaryNode(){};
    double value(void) const;
    void print(std::ostream &out=std::cout) const;
};

class FuncNode:public Node{
    std::string m_func_name;
    std::unique_ptr<Node> m_right;
public:
    FuncNode(const std::string &s,std::unique_ptr<Node> &&l):m_func_name(s),m_right(std::move(l)){};
    ~FuncNode(){};
    double value(void) const;
    void print(std::ostream &out=std::cout) const;
};

class BinaryNode:public Node{
    Kind m_kind;
    std::unique_ptr<Node> m_left;
    std::unique_ptr<Node> m_right;
public:
    BinaryNode(const Kind k,std::unique_ptr<Node> &l,std::unique_ptr<Node> &&r):m_kind(k),m_left(std::move(l)),m_right(std::move(r)){};
    ~BinaryNode(){};
    double value(void) const;
    void print(std::ostream &out=std::cout) const;
};
