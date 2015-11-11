#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>

class Expression;
class Logical;
class Relation;
class Primary;

class Parser
{
public:
    Parser();
    Parser(std::string src){
        m_str = src;
    }

    Expression * parse();
    static void test();
private:
    std::string m_str; //data, that would be parsed

    //METHODS
    static Expression * parseExpression(std::string);
    static Logical * parseLogical(std::string);
    static Relation * parseRelation(std::string);
    static Primary * parsePrimary(std::string);
    static std::vector<std::string> split(char*,const char[],int count_of_sign = 1,char *beg_pos = 0);
    static bool betweenBraces(std::string left,std::string right);
    static bool betweenBraces(std::string str);
};

#endif // PARSER_H
