#include "primary.h"
#include <stdexcept>

Primary::Primary()
{
    throw 1;
}

Primary::Primary(Expression * left, Expression * right,Primary::Opcode oper){
    if(!left or !right)
        throw new std::invalid_argument("Expression: null operands");
    m_left = left;
    m_right = right;
    op = oper;
}

Primary::Primary(std::string l, std::string r,Primary::Opcode oper){
    if(l.empty() or r.empty())
        throw new std::invalid_argument("Expression: null operands");
    left = l;
    right = r;
    op = oper;
}

long Primary::calculate(){
    if(op == INTEGER)
        return (long) m_val;
    if(op == PLUS)
        return m_left->calculate() + m_right->calculate();
    if(op == MINUS)
        return m_left->calculate() - m_right->calculate();
    if(op == PRODUCT)
        return m_left->calculate() * m_right->calculate();
    if(op == DEVIDE)
        return m_left->calculate() / m_right->calculate();
}
