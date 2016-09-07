#include "Node.h"
#include <math.h>
#include <map>
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
    if(m_op=="(") return m_right->value();
    if(m_op=="-") return -(m_right->value());
    throw calc_error("Invaild symbol");
}

void UnaryNode::print(ostream &out) const
{
    out<<m_op;
    m_right->print(out);
    if(m_op=="(") out<<")";
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

    auto iter=ftable.find(m_op);
    if(iter==ftable.end()) throw calc_error("Invaild function symbol\n");
    dout=iter->second(din);

    is_math_exception();
    return dout;
}

void UnaryFuncNode::print(ostream &out) const
{
    out<<m_op;
    m_right->print(out);
}

double BinaryNode::value(void) const
{
    static map<string, double(*)(double,double)> ftable {
            {"+",[](double a,double b)->double {return a+b;}},
            {"-",[](double a,double b)->double {return a-b;}},
            {"*",[](double a,double b)->double {return a*b;}},
            {"/",[](double a,double b)->double {return a/b;}},
            {"**",pow},
    };

    double dr=m_right->value();
    double dl=m_left->value();
    double dout=0.0;
    init_math_handler();

    auto iter=ftable.find(m_op);
    if(iter==ftable.end()) throw calc_error("Invaild symbol\n");
    dout=iter->second(dl,dr);

    is_math_exception();
    return dout;
}

void BinaryNode::print(ostream &out) const
{
    m_left->print(out);
    out<<m_op;
    m_right->print(out);
}


