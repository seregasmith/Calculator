#ifndef PRIMARY_H
#define PRIMARY_H
#include "expression.h"

class Primary : public Expression
{
public:
    enum Opcode{ PLUS, MINUS, PRODUCT, DEVIDE, INTEGER };
    Primary();
    Primary(std::string l, std::string r, Primary::Opcode oper);
    Primary(Expression * left, Expression * right,Primary::Opcode oper);
    Primary(long value){
        op = INTEGER;
        m_val = value;
    }

    long calculate();
    QJsonObject toJson();
private:
    Opcode op;
    std::string left;
    std::string right;
    long m_val;
    Expression * m_left;
    Expression * m_right;
};

#endif // PRIMARY_H
