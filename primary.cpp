#include "primary.h"
#include <stdexcept>
#include <stdio.h>
#include <QJsonDocument>
#include <QJsonObject>

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

QJsonObject Primary::toJson(){
    if(op == INTEGER)
    {
        QJsonObject * j_obj = new QJsonObject();
        j_obj->insert("value",QJsonValue((double)m_val));
        return *j_obj;
    }
    QString operation;
    if(op == PLUS) operation = "+";
    if(op == MINUS) operation = "-";
    if(op == PRODUCT) operation = "*";
    if(op == DEVIDE) operation = "/";
    QJsonObject left = m_left->toJson();
    QJsonObject right = m_right->toJson();
    QJsonObject * j_obj = new QJsonObject();
    j_obj->insert("left_operand",QJsonValue(left));
    j_obj->insert("right_operand",QJsonValue(right));
    j_obj->insert("operation",QJsonValue(operation));
    return *j_obj;
}
