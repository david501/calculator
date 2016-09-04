#include "calcuator.h"

calcuator::calcuator(std::istream &in,std::ostream &out):m_ts(in),m_out(out)
{
    run();
}

calcuator::calcuator(const std::string &sin,std::ostream &out):m_ts(sin),m_out(out)
{
    run();
}


calcuator::~calcuator()
{
    //dtor
}

void calcuator::run()
{
    m_table["pi"]=3.1415926535897932385;
    m_table["e"]=2.7182818284590452354;

    while(true){
        m_ts.get();
        if(m_ts.current().kind==Kind::end) break;
        if(m_ts.current().kind==Kind::print) continue;
        try{
            double d=expr(false);
            if(m_ts.current().kind==Kind::end || m_ts.current().kind==Kind::print)
                m_out<<d<<"\n";
            else
                m_out<<"Invaild symbol\n";
        }
        catch(calcuator_error &e){
            m_out<<e.what();
            break;
        }
    }
}

double calcuator::expr(bool b)
{
    double left=term(b);

    while(true) {
        switch(m_ts.current().kind){
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
        switch(m_ts.current().kind){
        case Kind::mul:
            left*=prim(true);
            break;
        case Kind::div:
            if(auto d=prim(true)){
                left/=d;
                break;
            }
            throw calcuator_error("divide by zero!");

        default:
            return left;
        }
    }
}

double calcuator::prim(bool b)
{
    if(b) m_ts.get();

    switch(m_ts.current().kind){
    case Kind::number:
        {
            double d=m_ts.current().number_value;
            m_ts.get();
            return d;
        }
    case Kind::name:
        {
            double &d=m_table[m_ts.current().string_value];
            m_ts.get();
            if(m_ts.current().kind==Kind::assign) {
                d=expr(true);
            }
            return d;
        }
    case Kind::minus:
        return -prim(true);
    case Kind::lp:
        {
            double d=expr(true);
            if(m_ts.current().kind!=Kind::rp) throw calcuator_error("')' expected");
            m_ts.get();
            return d;
        }
    default:
        throw calcuator_error("primary expected");
    }
    return 0.0;
}
