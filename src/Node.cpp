#include "Node.h"
#include <math.h>
#include <string>
#include <algorithm>
#include <fenv.h>

using namespace std;

Node::Node()
{
    //ctor
}

Node::~Node()
{
    //dtor
}

void Node::init_math_handler() const
{
    if (math_errhandling & MATH_ERREXCEPT) feclearexcept(FE_ALL_EXCEPT);
}

void Node::is_math_exception() const
{
    if (math_errhandling & MATH_ERRNO) {
        if (errno==EDOM) throw calc_error("errno set to EDOM\n");
        if (errno==ERANGE) throw calc_error("errno set to ERANGE\n");
    }
    if (math_errhandling  &MATH_ERREXCEPT) {
        if (fetestexcept(FE_INVALID)) throw calc_error("FE_INVALID raised\n");
    }
}

double NumberNode::value(void) const
{
    return m_number;
}

void NumberNode::print(ostream &out) const
{
    out<<m_number;
}


double UnaryNode::value(void) const
{
    switch(m_kind)
    {
        case Kind::lp: return m_right->value();
        case Kind::minus: return -(m_right->value());
        default:
            throw calc_error("Invaild symbol");
    }
}

void UnaryNode::print(ostream &out) const
{
     switch(m_kind)
    {
        case Kind::lp: out<<"(";m_right->print(out);out<<")";break;
        case Kind::minus: out<<"-";m_right->print(out);break;
        default:
            throw calc_error("Invaild symbol");
    }
}


double UnaryFuncNode::value(void) const
{
    static map<string, double(*)(double)> ftable {{"sin",sin},{"cos", cos},{"tan", tan},
                                                {"asin",asin},{"acos",acos},{"atan",atan},
                                                {"sqrt",sqrt},{"log", log10},{"ln", log},
                                                };
    double din=m_right->value();
    double dout=0.0;

    init_math_handler();

    auto iter=ftable.find(m_func_name);
    if(iter==ftable.end()) throw calc_error("Invaild function symbol\n");
    dout=iter->second(din);

    is_math_exception();
    return dout;
}

void UnaryFuncNode::print(ostream &out) const
{
    out<<m_func_name;
    m_right->print(out);
}

double BinaryNode::value(void) const
{
    double dr=m_right->value();
    double dl=m_left->value();
    double dout=0.0;
    init_math_handler();

    switch(m_kind)
    {
        case Kind::plus:    dout= dl+dr;break;
        case Kind::minus:   dout= dl-dr;break;
        case Kind::mul:     dout= dl*dr;break;
        case Kind::div:     dout= dl/dr;break;
        case Kind::power:   dout=pow(dl,dr);break;
        default:
            throw calc_error("Invaild symbol\n");
    }

    is_math_exception();
    return dout;
}

void BinaryNode::print(ostream &out) const
{
    m_left->print(out);
    if(m_kind==Kind::power)
        out<<"**";
    else
        out<<static_cast<char>(m_kind);
    m_right->print(out);
}


