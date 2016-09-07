#pragma once

#include <iostream>
#include <memory>

struct calc_error: std::runtime_error
{
    calc_error(const std::string &s):std::runtime_error(s){};
};

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
        void init_math_handler() const;
        void is_math_exception() const;
    private:
};

class NumberNode:public Node{
    double m_number;
public:
    NumberNode(const double d):m_number(d){};
    ~NumberNode(){};
    double value(void) const;
    void print(std::ostream &out=std::cout) const;
};

class UnaryNode:public Node{
    std::string m_op;
    std::unique_ptr<Node> m_right;
public:
    UnaryNode(const std::string &op,std::unique_ptr<Node> &&l):m_op(op),m_right(std::move(l)){};
    ~UnaryNode(){};
    double value(void) const;
    void print(std::ostream &out=std::cout) const;
};

class UnaryFuncNode:public Node{
    std::string m_op;
    std::unique_ptr<Node> m_right;

public:
    UnaryFuncNode(const std::string &s,std::unique_ptr<Node> &&l):m_op(s),m_right(std::move(l)){};
    ~UnaryFuncNode(){};
    double value(void) const;
    void print(std::ostream &out=std::cout) const;
};

class BinaryNode:public Node{
    std::string m_op;
    std::unique_ptr<Node> m_left;
    std::unique_ptr<Node> m_right;
public:
    BinaryNode(const std::string &s,std::unique_ptr<Node> &l,std::unique_ptr<Node> &&r):m_op(s),m_left(std::move(l)),m_right(std::move(r)){};
    ~BinaryNode(){};
    double value(void) const;
    void print(std::ostream &out=std::cout) const;
};
