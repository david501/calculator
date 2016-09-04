#include "Node.h"
#include <math.h>
#include <string>
#include <algorithm>

//Node::m_func_table

Node::Node()
{
    //ctor
}

Node::~Node()
{
    //dtor
}



void NumberNode::print(std::ostream &out) const
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
void UnaryNode::print(std::ostream &out) const
{
     switch(m_kind)
    {
        case Kind::lp: out<<"(";m_right->print(out);out<<")";break;
        case Kind::minus: out<<"-";m_right->print(out);break;
        default:
            throw calc_error("Invaild symbol");
    }
}

FKind get_FKind(std::string s)
{
    static std::map<std::string, FKind> ftable {{"sin",FKind::sin},{"cos",FKind::cos},{"tan",FKind::tan}};

    if(ftable.find(s)==ftable.end()) return FKind::nofunc;
    return ftable[s];
}

double FuncNode::value(void) const
{
    FKind fkind=get_FKind(m_func_name);
    switch(fkind)
    {
        case FKind::sin: return sin(m_right->value());
        case FKind::cos: return cos(m_right->value());
        case FKind::tan: return tan(m_right->value());
        default:
            throw calc_error("Invaild symbol");
    }
}

void FuncNode::print(std::ostream &out) const
{
    out<<m_func_name;
    m_right->print(out);
}

double BinaryNode::value(void) const
{
    switch(m_kind)
    {
        case Kind::plus:    return m_left->value()+m_right->value();
        case Kind::minus:   return m_left->value()-m_right->value();
        case Kind::mul:     return m_left->value()*m_right->value();
        case Kind::div:
            {
                if(double d=m_right->value())
                    return m_left->value()/d;
                throw calc_error("divide by zero!");
            }
        case Kind::power:   return pow(m_left->value(),m_right->value());
        default:
            throw calc_error("Invaild symbol");
    }
}

void BinaryNode::print(std::ostream &out) const
{
    m_left->print(out);
    if(m_kind==Kind::power)
        out<<"**";
    else
        out<<static_cast<char>(m_kind);
    m_right->print(out);
}


