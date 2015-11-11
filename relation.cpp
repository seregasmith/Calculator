#include "relation.h"
#include <stdexcept>
#include <QJsonDocument>
#include <QJsonObject>

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

QJsonObject Relation::toJson(){
    QString operation;
    if(op == MORE_EQ) operation = ">=";
    if(op == LESS_EQ) operation = "<=";
    if(op == MORE) operation = ">";
    if(op == LESS) operation = "<";
    if(op == EQUAL) operation = "=";
    if(op == NOT_EQUAL) operation = "/=";
    QJsonObject left = m_left->toJson();
    QJsonObject right = m_right->toJson();
    QJsonObject * j_obj = new QJsonObject();
    j_obj->insert("left_operand",QJsonValue(left));
    j_obj->insert("right_operand",QJsonValue(right));
    j_obj->insert("operation",QJsonValue(operation));
    return *j_obj;
}
