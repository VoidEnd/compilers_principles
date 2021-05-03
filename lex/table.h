//
// Created by 13990 on 2021/4/15.
//

#ifndef LEX_TABLE_H
#define LEX_TABLE_H

# include <iostream>

using namespace std;

class table{

public:
    int digit = 0;
    int letter = 1;

    string KEYWORD[6] = {
            "int", "while", "if", "else", "get", "put"
    }; // 关键字

    string OPERATOR[14] = {
            "+", "-", "=", "==", "<>", ">", ">=", "<", "<=", "&&", "&", "||", "|", "!"
    }; // 运算符

    char SEPARATER[6] = {
            ';', ',', '{', '}', '(', ')'
    }; // 分隔符

    string ANNOTATOR[3] = {
            "//", "/*", "*/"
    }; // 注释符

    char FILTER[4] = {
            ' ', '\t', '\r', '\n'
    }; // 过滤符

    string TOTAL[34] = {
            "digit", "letter", "int", "while", "if", "else", "get", "put",
            "+", "-", "*", "/", "=", "==", "<>", ">", ">=", "<", "<=", "&&",
            "&", "||", "|", "!", "!=", ";", ",", "{", "}", "(", ")", "//",
            "/*", "*/"
    };
};

#endif //LEX_TABLE_H
