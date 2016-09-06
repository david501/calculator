#include "CalcN.h"
using namespace std;

CalcN::CalcN()
{
    m_table["pi"]=3.1415926535897932385;
    m_table["e"]=2.7182818284590452354;
}

CalcN::~CalcN()
{
    //dtor
}

void CalcN::operator()(istream &in,std::ostream &out)
{
    m_out=&out;
    m_ts=unique_ptr<Token_Stream> (new Token_Stream(in));
    run();
}

string CalcN::operator()(const string &s)
{
    istringstream iss(s);
    ostringstream oss;
    (*this)(iss,oss);
    return oss.str();
}


void CalcN::run()
{
    while(true)
    {
        try
        {
            m_ts->get();
            if(m_ts->current().kind==Kind::end) break;
            if(m_ts->current().kind==Kind::print) continue;

            unique_ptr<Node> N=move(expr(false));
            if(m_ts->current().kind==Kind::end || m_ts->current().kind==Kind::print)
            {
                //N->print();cout<<endl;
                *m_out<<N->value()<<"\n";
            }
            else
                throw calc_error ("Invaild symbol\n");
        }
        catch(calc_error &e)
        {
            *m_out<<e.what();
            while (m_ts->current().kind!=Kind::end && m_ts->current().kind!=Kind::print) m_ts->get();
        }
    }
}

unique_ptr<Node> CalcN::expr(bool b)
{
    unique_ptr<Node> left=move(term(b));

    while(true)
    {
        Kind kind=m_ts->current().kind;
        switch(kind)
        {
        case Kind::plus:
        case Kind::minus:
            left=unique_ptr<Node>(new BinaryNode(kind,left,term(true)));
            break;
        default:
            return move(left);
        }
    }
}

unique_ptr<Node> CalcN::term(bool b)
{
    unique_ptr<Node> left =move(prim(b));

    while(true)
    {
        Kind kind=m_ts->current().kind;
        switch(kind)
        {
            case Kind::mul:
                if(m_ts->get().kind==kind)
                    left=std::unique_ptr<Node> (new BinaryNode(Kind::power,left,prim(true)));
                else
                    left=std::unique_ptr<Node> (new BinaryNode(kind,left,prim(false)));
                break;
            case Kind::div:
                left=std::unique_ptr<Node> (new BinaryNode(kind,left,prim(true)));
                break;
            default:
                return move(left);
        }
    }
}

unique_ptr<Node> CalcN::prim(bool b)
{
    if(b) m_ts->get();

    switch(m_ts->current().kind)
    {
        case Kind::number:
            {
                double d=m_ts->current().number_value;
                m_ts->get();
                return unique_ptr<Node> (new NumberNode(d));
            }
        case Kind::name:
            {
                string name=m_ts->current().string_value;
                m_ts->get();

                // function(x)
                if(m_ts->current().kind==Kind::lp)
                {
                    return unique_ptr<Node> (new UnaryFuncNode(name, prim(false)));
                }

                // name=123456;
                double &d=m_table[name];
                if(m_ts->current().kind==Kind::assign) {
                    d=expr(true)->value();
                }
                return unique_ptr<Node> (new NumberNode(d));
            }
        case Kind::minus:
            {   // -(expr)
                return unique_ptr<Node> (new UnaryNode(Kind::minus, prim(true)));
            }
        case Kind::lp:
            {   // ( expr )
                std::unique_ptr<Node> tmp=move(expr(true));
                if(m_ts->current().kind!=Kind::rp) throw calc_error("')' expected");
                m_ts->get();
                return unique_ptr<Node> (new UnaryNode(Kind::lp, move(tmp)));
            }
        default:
            throw calc_error("primary expected");
    }
}


