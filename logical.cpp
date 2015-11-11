#include "logical.h"
#include <stdexcept>

Logical::Logical()
{
}

Logical::Logical(Expression * left, Expression * right,Logical::Opcode oper){
    if(!left or !right)
        throw new std::invalid_argument("Logical: null operands");
    m_left = left;
    m_right = right;
    op = oper;
}

long Logical::calculate(){
    bool left = m_left->calculate() == 0 ? false : true;
    bool right = m_right->calculate() == 0 ? false : true;
    if( op == AND )
        return (left and right) ? 1 : 0;
    if( op == OR )
        return (left or right) ? 1 : 0;
    if( op == XOR )
        return (left xor right) ? 1 : 0;
}
