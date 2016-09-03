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
        //m_out<<expr(false)<<"\n";
        m_out<<m_ts.current().number_value<<"\n";
    }

}

double calcuator::expr(bool b)
{
    return 0.0;
}
