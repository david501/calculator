#include "Token.h"
#include <stdlib.h>


Token_Stream::Token_Stream(std::istream &in):m_iss(""),m_is(&in)
{
    //ctor
}

Token_Stream::Token_Stream(const std::string s):m_iss(s),m_is(nullptr)
{
    m_is=&m_iss;
}

Token_Stream::~Token_Stream()
{
    //dtor
}

Token Token_Stream::get()
{
    char c;

    do
    {
        if(!m_is->get(c)) return m_cur={Kind::end};

    }while(c!='\n' && isspace(c));

    switch(c)
    {
        case '\n': case ';':
            return m_cur={Kind::print};
        case '+': case '-': case '*': case '/':
        case '=':
        case '(': case ')':
            return m_cur={static_cast<Kind> (c)};
        case '0':case '1': case '2':case '3': case '4':case '5': case '6':case '7': case '8':case '9':
        case '.':
            m_is->putback(c);
            *m_is>>m_cur.number_value;
            m_cur.kind=Kind::number;
            return m_cur;
        default:
            if(isalpha(c))
            {
                m_cur.string_value=c;
                while(m_is->get(c) && isalnum(c))
                {
                     m_cur.string_value+=c;
                }
                m_is->putback(c);
                m_cur.kind=Kind::name;
                return m_cur;
            }
            return m_cur={Kind::end};
    }
}
