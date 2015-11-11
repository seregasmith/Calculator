#include "logical.h"
#include <stdexcept>
#include <QJsonObject>
#include <QJsonDocument>

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

QJsonObject Logical::toJson(){
    QString operation;
    if(op == AND) operation = "and";
    if(op == OR) operation = "or";
    if(op == XOR) operation = "xor";
    QJsonObject left = m_left->toJson();
    QJsonObject right = m_right->toJson();
    QJsonObject * j_obj = new QJsonObject();
    j_obj->insert("left_operand",QJsonValue(left));
    j_obj->insert("right_operand",QJsonValue(right));
    j_obj->insert("operation",QJsonValue(operation));
    return *j_obj;
}
