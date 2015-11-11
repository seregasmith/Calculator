#ifndef LOGICAL_H
#define LOGICAL_H
#include "expression.h"

class Logical : public Expression
{
public:
    enum Opcode{ AND, OR, XOR, NONE }; // NONE isn't used
    Logical();
    Logical(std::string left, std::string right);
    Logical(Expression * left, Expression * right,Logical::Opcode oper);
    long calculate();
    QJsonObject toJson();
private:
    Opcode op;
    std::string left;
    std::string right;
    Expression * m_left;
    Expression * m_right;
};

#endif // LOGICAL_H
