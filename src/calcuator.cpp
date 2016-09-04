#include <sstream>
#include "calcuator.h"


calcuator::calcuator():m_ts(nullptr)
{
    m_table["pi"]=3.1415926535897932385;
    m_table["e"]=2.7182818284590452354;
}

calcuator::~calcuator()
{
}

void calcuator::operator()(std::istream &in,std::ostream &out)
{
    m_out=&out;
    m_ts=std::unique_ptr<Token_Stream> (new Token_Stream(in));
    run();
}

std::string calcuator::operator()(const std::string &sin)
{
    std::istringstream iss(sin);
    std::ostringstream oss;
    (*this)(iss,oss);
    return oss.str();
}


void calcuator::run()
{
    while(true){
        try{
            m_ts->get();
            if(m_ts->current().kind==Kind::end) break;
            if(m_ts->current().kind==Kind::print) continue;

            double d=expr(false);
            if(m_ts->current().kind==Kind::end || m_ts->current().kind==Kind::print)
                *m_out<<d<<"\n";
            else
                *m_out<<"Invaild symbol\n";
        }
        catch(calc_error &e){
            *m_out<<e.what();
            break;
        }
    }
}

double calcuator::expr(bool b)
{
    double left=term(b);

    while(true) {
        switch(m_ts->current().kind){
        case Kind::plus:
            left+=term(true);
            break;
        case Kind::minus:
            left-=term(true);
            break;
        default:
            return left;
        }
    }
}

double calcuator::term(bool b)
{
    double left=prim(b);

    while(true) {
        switch(m_ts->current().kind){
        case Kind::mul:
            left*=prim(true);
            break;
        case Kind::div:
            if(auto d=prim(true)){
                left/=d;
                break;
            }
            throw calc_error("divide by zero!");

        default:
            return left;
        }
    }
}

double calcuator::prim(bool b)
{
    if(b) m_ts->get();

    switch(m_ts->current().kind){
    case Kind::number:
        {
            double d=m_ts->current().number_value;
            m_ts->get();
            return d;
        }
    case Kind::name:
        {
            double &d=m_table[m_ts->current().string_value];
            m_ts->get();
            if(m_ts->current().kind==Kind::assign) {
                d=expr(true);
            }
            return d;
        }
    case Kind::minus:
        return -prim(true);
    case Kind::lp:
        {
            double d=expr(true);
            if(m_ts->current().kind!=Kind::rp) throw calc_error("')' expected");
            m_ts->get();
            return d;
        }
    default:
        throw calc_error("primary expected");
    }
    return 0.0;
}
