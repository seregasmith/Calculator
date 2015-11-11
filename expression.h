#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>

class Expression
{

public:
    Expression();
    Expression(std::string);

    virtual long calculate(){
        ///TODO: implement
        return -1;
    }
};

#endif // EXPRESSION_H
