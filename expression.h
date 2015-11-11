#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <QJsonObject>

class Expression
{

public:
    Expression();
    Expression(std::string);

    virtual long calculate(){
        ///TODO: implement
        return -1;
    }
    virtual QJsonObject toJson(){}
};

#endif // EXPRESSION_H
