#include "relation.h"
#include <stdexcept>

Relation::Relation()
{
    throw 1;
}

Relation::Relation(Expression * left, Expression * right,Relation::Opcode oper){
    if(!left or !right)
        throw new std::invalid_argument("Logical: null operands");
    m_left = left;
    m_right = right;
    op = oper;
}

Relation::Relation(std::string l, std::string r,Relation::Opcode oper){
    if(l.empty() or r.empty())
        throw new std::invalid_argument("Relation: null operands");
    left = l;
    right = r;
    op = oper;
}

long Relation::calculate(){
    if(op == MORE_EQ)
        if(m_left->calculate() >= m_right->calculate())
            return 1;
        else
            return 0;
    if(op == LESS_EQ)
        if(m_left->calculate() <= m_right->calculate())
            return 1;
        else
            return 0;
    if(op == MORE)
        if(m_left->calculate() > m_right->calculate())
            return 1;
        else
            return 0;
    if(op == LESS)
        if(m_left->calculate() < m_right->calculate())
            return 1;
        else
            return 0;
    if(op == EQUAL)
        if(m_left->calculate() == m_right->calculate())
            return 1;
        else
            return 0;
    if(op == NOT_EQUAL)
        if(m_left->calculate() != m_right->calculate())
            return 1;
        else
            return 0;
}
