#ifndef RELATION_H
#define RELATION_H
#include "expression.h"

class Relation : public Expression
{
public:
    enum Opcode{ MORE_EQ, LESS_EQ, LESS, MORE, EQUAL, NOT_EQUAL };
    Relation();
    Relation(std::string l, std::string r, Relation::Opcode oper);
    Relation(Expression * left, Expression * right,Relation::Opcode oper);
    long calculate();
private:
    Opcode op;
    std::string left;
    std::string right;
    Expression * m_left;
    Expression * m_right;
};

#endif // RELATION_H
