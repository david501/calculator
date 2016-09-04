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

string CalcN::operator()(const string &sin)
{
    istringstream iss(sin);
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
            {
                *m_out<<"Invaild symbol\n";
                break;
            }
        }
        catch(calc_error &e)
        {
            *m_out<<e.what();
            break;
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
            {
                if(m_ts->get().kind==kind)
                    left=std::unique_ptr<Node> (new BinaryNode(Kind::power,left,prim(true)));
                else
                    left=std::unique_ptr<Node> (new BinaryNode(kind,left,prim(false)));
                break;
            }
            case Kind::div:
            {
                left=std::unique_ptr<Node> (new BinaryNode(kind,left,prim(true)));
                break;
            }
            default:
                return move(left);
        }
    }
}

unique_ptr<Node> CalcN::prim(bool b)
{
    unique_ptr<Node> left;

    if(b) m_ts->get();

    switch(m_ts->current().kind)
    {
        case Kind::number:
            {
                double d=m_ts->current().number_value;
                m_ts->get();
                left=unique_ptr<Node> (new NumberNode(d));
                break;
            }
        case Kind::name:
            {
                string name=m_ts->current().string_value;
                FKind fk=get_FKind(name);
                if(fk!=FKind::nofunc) {
                    m_ts->get();
                    if(m_ts->current().kind!=Kind::lp) throw calc_error("'(' expected");
                    left=unique_ptr<Node> (new FuncNode(name, prim(false)));
                    break;
                }
                double &d=m_table[name];
                m_ts->get();
                if(m_ts->current().kind==Kind::assign) {
                    d=expr(true)->value();
                }
                left=unique_ptr<Node> (new NumberNode(d));
                break;
            }
        case Kind::minus:
            {
                left=unique_ptr<Node> (new UnaryNode(Kind::minus, prim(true)));
                break;
            }
        case Kind::lp:
            {
                std::unique_ptr<Node> tmp=move(expr(true));
                if(m_ts->current().kind!=Kind::rp) throw calc_error("')' expected");
                m_ts->get();
                left=unique_ptr<Node> (new UnaryNode(Kind::lp, move(tmp)));
                break;
            }
        default:
            throw calc_error("primary expected");
    }
    return move(left);
}


