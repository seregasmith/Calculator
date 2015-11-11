#include "parser.h"

#include "expression.h"
#include "logical.h"
#include "primary.h"
#include "relation.h"

#include <QString>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <map>

////TEST
#include <QJsonDocument>
//#include <QJsonObject>

void Parser::test(){
    std::string str = "(10+9)/10>0xor(10+9)*4=0";
//    std::string str = "5+4";
    Expression * expressionTree = parseExpression(str);

    long result = expressionTree->calculate();
    QJsonObject result_json = expressionTree->toJson();
    QJsonDocument j_doc(result_json);

    std::cout << "RESULT: "<< result <<"\n";
    std::cout << "RESULT JSON: "<< QString(j_doc.toJson()).toStdString() <<"\n";
//    QJsonObject * j_obj = new QJsonObject();
//    j_obj->insert("left_operand",QJsonValue(2));
//    j_obj->insert("right_operand",QJsonValue(3));
//    j_obj->insert("operation",QJsonValue("+"));
//    QJsonDocument * j_doc = new QJsonDocument(*j_obj);
//    QString str(j_doc->toJson());
//    std::cout << "RESULT: "<< str.toStdString() <<"\n";
}

Expression * Parser::parse(){
    return parseExpression(m_str);
}

Expression * Parser::parseExpression(std::string str){
    Expression * result;
    result = parseLogical(str);
    if(result)
        return result;
    result = parseRelation(str);
    if(result)
        return result;
    result = parsePrimary(str);
    if(result)
        return result;

    return result;
}

Logical * Parser::parseLogical(std::string str)
{

    std::vector<std::string> res;
    Logical::Opcode op;
    //>=, <=, >, <
    try{
        std::map<std::vector<std::string>, Logical::Opcode> maps;
        maps.insert(
                    std::pair<std::vector<std::string>, Logical::Opcode>(
                        split((char*)str.c_str(),"and",3),Logical::Opcode::AND
                        )
                    );
        maps.insert(
                    std::pair<std::vector<std::string>, Logical::Opcode>(
                        split((char*)str.c_str(),"or",2),Logical::Opcode::OR
                        )
                    );
        maps.insert(
                    std::pair<std::vector<std::string>, Logical::Opcode>(
                        split((char*)str.c_str(),"xor",3),Logical::Opcode::XOR
                        )
                    );
        int min_size = 0;
        for(std::map<std::vector<std::string>, Logical::Opcode>::iterator it = maps.begin();it != maps.end(); it++){
            std::vector<std::string> operands = it->first;
            Logical::Opcode opc = it->second;
            if( operands.size() == 2 ){
                if (min_size == 0 or min_size > operands[0].length()){
                    res = operands;
                    op = opc;
                    min_size = operands[0].length();
                }
            }
        }
    }catch(std::invalid_argument e){
        std::cerr << e.what() << std::endl;
    }
    if(!res.empty()){
//        return new Logical(res[0],res[1], op);
        return new Logical(parseExpression(res[0]),parseExpression(res[1]), op);
    }

    return 0;
}
Relation * Parser::parseRelation(std::string str)
{

    std::vector<std::string> res;
    Relation::Opcode op;
    //>=, <=, >, <
    try{
        std::map<std::vector<std::string>, Relation::Opcode> maps;
        maps.insert(
                    std::pair<std::vector<std::string>, Relation::Opcode>(
                        split((char*)str.c_str(),">=",2),Relation::Opcode::MORE_EQ
                        )
                    );
        maps.insert(
                    std::pair<std::vector<std::string>, Relation::Opcode>(
                        split((char*)str.c_str(),"<=",2),Relation::Opcode::LESS_EQ
                        )
                    );
        maps.insert(
                    std::pair<std::vector<std::string>, Relation::Opcode>(
                        split((char*)str.c_str(),">"),Relation::Opcode::MORE
                        )
                    );
        maps.insert(
                    std::pair<std::vector<std::string>, Relation::Opcode>(
                        split((char*)str.c_str(),"<"),Relation::Opcode::LESS
                        )
                    );
        maps.insert(
                    std::pair<std::vector<std::string>, Relation::Opcode>(
                        split((char*)str.c_str(),"="),Relation::Opcode::EQUAL
                        )
                    );
        maps.insert(
                    std::pair<std::vector<std::string>, Relation::Opcode>(
                        split((char*)str.c_str(),"/=",2),Relation::Opcode::NOT_EQUAL
                        )
                    );
        int min_size = 0;
        for(std::map<std::vector<std::string>, Relation::Opcode>::iterator it = maps.begin();it != maps.end(); it++){
            std::vector<std::string> operands = it->first;
            Relation::Opcode opc = it->second;
            if( operands.size() == 2 ){
                if (min_size == 0 or min_size > operands[0].length()){
                    res = operands;
                    op = opc;
                    min_size = operands[0].length();
                }
            }
        }
    }catch(std::invalid_argument e){
        std::cerr << e.what() << std::endl;
    }
    if(!res.empty()){
//        return new Relation(res[0],res[1], op);
        return new Relation(parseExpression(res[0]),parseExpression(res[1]), op);
    }

    return 0;
}

Primary * Parser::parsePrimary(std::string str)
{

    std::vector<std::string> res;
    Primary::Opcode op;
    //+, -
    try{
        std::map<std::vector<std::string>, Primary::Opcode> maps;
        maps.insert(
                    std::pair<std::vector<std::string>, Primary::Opcode>(
                        split((char*)str.c_str(),"+"),Primary::Opcode::PLUS
                        )
                    );
        maps.insert(
                    std::pair<std::vector<std::string>, Primary::Opcode>(
                        split((char*)str.c_str(),"-"),Primary::Opcode::MINUS
                        )
                    );
        //Finding the closest operation
        int min_size = 0;
        for(std::map<std::vector<std::string>, Primary::Opcode>::iterator it = maps.begin();it != maps.end(); it++)
        {
            std::vector<std::string> operands = it->first;
            Primary::Opcode opc = it->second;
            if( operands.size() == 2 )
            {
                if (min_size == 0 or min_size > operands[0].length())
                {
                    res = operands;
                    op = opc;
                    min_size = operands[0].length();
                }
            }
        }
    }catch(std::invalid_argument e){
        std::cerr << e.what() << std::endl;
    }
    if(!res.empty()){
//        return new Primary(res[0],res[1], op);
        return new Primary(parseExpression(res[0]),parseExpression(res[1]), op);
    }

    //*,/
    try{
        std::map<std::vector<std::string>, Primary::Opcode> maps;
        maps.insert(
                    std::pair<std::vector<std::string>, Primary::Opcode>(
                        split((char*)str.c_str(),"*"),Primary::Opcode::PRODUCT
                        )
                    );
        maps.insert(
                    std::pair<std::vector<std::string>, Primary::Opcode>(
                        split((char*)str.c_str(),"/"),Primary::Opcode::DEVIDE
                        )
                    );
        //Finding the closest operation
        int min_size = 0;
        for(std::map<std::vector<std::string>, Primary::Opcode>::iterator it = maps.begin();it != maps.end(); it++)
        {
            std::vector<std::string> operands = it->first;
            Primary::Opcode opc = it->second;
            if( operands.size() == 2 )
            {
                if (min_size == 0 or min_size > operands[0].length())
                {
                    res = operands;
                    op = opc;
                    min_size = operands[0].length();
                }
            }
        }
    }catch(std::invalid_argument e){
        std::cerr << e.what() << std::endl;
    }
    if(!res.empty()){
//        return new Primary(res[0],res[1], op);
        return new Primary(parseExpression(res[0]),parseExpression(res[1]), op);
    }

    bool ok;
    QString tmp_str(str.c_str());
    int val = tmp_str.toInt(&ok, 10);
    if(ok){
        return new Primary(val);
    }

    if(betweenBraces(str)){
        std::string tmp_str = str;
        tmp_str.erase(tmp_str.length()-1);
        tmp_str.erase(0,1);
        return (Primary*) parseExpression(tmp_str);
    }


    return 0;
}


std::vector<std::string> Parser::split(char * expression_str, const char operation_str[],int count_of_sign, char * beg_pos )
{
    const char *pos;
    if(beg_pos)
        pos = strstr( beg_pos, operation_str);
    else
        pos = strstr(expression_str, operation_str);
    if (!pos)
        return std::vector<std::string>();

    std::string left(expression_str);
    left = left.substr(0,pos - expression_str);

    //shift by signs of operation
    for(int i=0;i<count_of_sign;i++)
        pos++;
    std::string right(pos);

    if(betweenBraces(left,right))
    {
        std::vector<std::string> v;
        v = split(expression_str,operation_str, count_of_sign,(char*)pos);
        if(v.size() > 0){
            left = v[0];
            right = v[1];
        }else
             return v;

    }
    std::vector<std::string> res_arr = {left,right};
    return res_arr;
}

bool Parser::betweenBraces(std::string left,std::string right)
{
    if(
            std::count(left.begin(), left.end(), '(') + std::count(right.begin(), right.end(), '(')
            !=
            std::count(left.begin(), left.end(), ')') + std::count(right.begin(), right.end(), ')')
            )
    {
        //Exception throwing part
        std::stringstream stream;
        stream << "Parser: Unclosed braces. "<< left<< " <SIGN> "<< right;
        throw std::invalid_argument( stream.str().c_str());
    }
    int count_left = std::count(left.begin(), left.end(), '(') - std::count(left.begin(), left.end(), ')');
    int count_right = std::count(right.begin(), right.end(), '(') - std::count(right.begin(), right.end(), ')');
    return count_left != count_right;
}

bool Parser::betweenBraces(std::string str)
{
    auto it_b = str.begin();
    auto it_e = str.end();
    if(str.front() == '(' and str.back() == ')')
        return true;
    else
        return false;
}

