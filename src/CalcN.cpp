#include "CalcN.h"

CalcN::CalcN()
{
    m_table["pi"]=3.1415926535897932385;
    m_table["e"]=2.7182818284590452354;
}

CalcN::~CalcN()
{
    //dtor
}

void CalcN::operator()(std::istream &in,std::ostream &out)
{
    m_out=&out;
    m_ts=std::unique_ptr<Token_Stream> (new Token_Stream(in));
    run();
}

std::string CalcN::operator()(const std::string &sin)
{
    std::istringstream iss(sin);
    std::ostringstream oss;
    (*this)(iss,oss);
    return oss.str();
}


void CalcN::run()
{
    while(true){
        m_ts->get();
        if(m_ts->current().kind==Kind::end) break;
        if(m_ts->current().kind==Kind::print) continue;
        try{
            std::shared_ptr<Node> N=expr(false);
            if(m_ts->current().kind==Kind::end || m_ts->current().kind==Kind::print)
                *m_out<<N->value()<<"\n";
            else
                *m_out<<"Invaild symbol\n";
        }
        catch(calc_error &e){
            *m_out<<e.what();
            break;
        }
    }
}

std::shared_ptr<Node> CalcN::expr(bool b)
{
    std::shared_ptr<Node> left=term(b);

    while(true) {
        switch(m_ts->current().kind){
        case Kind::plus:
        case Kind::minus:

            left=std::shared_ptr<Node>(new Node(m_ts->current().kind,left,term(true)));
            break;
        default:
            return left;
        }
    }
}

std::shared_ptr<Node> CalcN::term(bool b)
{
    std::shared_ptr<Node> left =(prim(b));

    while(true) {
        switch(m_ts->current().kind){
        case Kind::mul:
        case Kind::div:
        {
            left=std::shared_ptr<Node> (new Node(m_ts->current().kind,left,prim(true)));
            break;
        }
        default:
            return left;
        }
    }
}

std::shared_ptr<Node> CalcN::prim(bool b)
{
    if(b) m_ts->get();

    switch(m_ts->current().kind){
    case Kind::number:
        {
            double d=m_ts->current().number_value;
            m_ts->get();
            return std::shared_ptr<Node> (new Node(Kind::number,d));
        }
    case Kind::name:
        {
            double &d=m_table[m_ts->current().string_value];
            m_ts->get();
            if(m_ts->current().kind==Kind::assign) {
                d=expr(true)->value();
            }
            return std::shared_ptr<Node> (new Node(Kind::number,d));
        }
    case Kind::minus:
    {
            return std::shared_ptr<Node> (new Node(Kind::minus, prim(true)));
    }
    case Kind::lp:
        {
            std::shared_ptr<Node> left=(expr(true));
            if(m_ts->current().kind!=Kind::rp) throw calc_error("')' expected");
            m_ts->get();
            return std::shared_ptr<Node> (new Node(Kind::lp, left));
        }
    default:
        throw calc_error("primary expected");
    }
}


double Node::value(void) const
{
    switch(kind){
    case Kind::number: return number;
    case Kind::plus: return left->value()+right->value();
    case Kind::lp: return left->value();
    case Kind::minus: return (right!=nullptr) ? left->value()-right->value(): -(left->value());
    case Kind::mul: return left->value()*right->value();
    case Kind::div:
        {
            if(double d=right->value())
                return left->value()/d;
            throw calc_error("divide by zero!");
        }
    default:
        throw calc_error("Invaild symbol");
    }
}
