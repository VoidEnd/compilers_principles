//
// Created by 13990 on 2021/4/15.
//

#ifndef LEX_JUDGE__TOOLS_H
#define LEX_JUDGE__TOOLS_H

#include "table.h"

class judgeTool {

public:
    table t;

    // 判断是否为关键字
    bool IsKeyword(string word) {
        for (int i = 0; i < 6; i++) {
            if (t.KEYWORD[i] == word) {
                return true;
            }
        }
        return false;
    }

    // 判断是否为分隔符
    bool IsSeparater(char ch) {
        for (int i = 0; i < 6; i++) {
            if (t.SEPARATER[i] == ch) {
                return true;
            }
        }
        return false;
    }

    // 判断是否为运算符
    bool IsOperator(string ch) {
        for (int i = 0; i < 12; i++) {
            if (t.OPERATOR[i] == ch) {
                return true;
            }
        }
        return false;
    }

    // 判断是否为注释符
    bool IsAnnotator(string st) {
        for (int i = 0; i < 3; i++) {
            if (t.ANNOTATOR[i] == st) {
                return true;
            }
        }
        return false;
    }

    // 判断是否为过滤符
    bool IsFilter(char ch) {
        for (int i = 0; i < 4; i++) {
            if (t.FILTER[i] == ch) {
                return true;
            }
        }
        return false;
    }

    // 判断是否为大写字母
    bool IsUpLetter(char ch) {
        if (ch >= 'A' && ch <= 'Z') return true;
        return false;
    }

    // 判断是否为小写字母
    bool IsLowLetter(char ch) {
        if (ch >= 'a' && ch <= 'z') return true;
        return false;
    }

    // 判断是否为数字
    bool IsDigit(char ch) {
        if (ch >= '0' && ch <= '9') return true;
        return false;
    }

    // 判断是否为数字或变量的正常结尾
    bool IsEnd(char ch) {
        if (ch != ' ' && ch != '\n' && ch != ';' && ch != ',' && ch != ')') return true;
        return false;
    }

    // 判断是否为8进制数字
    bool IsDigit8(char ch) {
        if (ch >= '0' && ch <= '7') return true;
        return false;
    }

    // 判断是否为16进制数字
    bool IsDigit16(char ch) {
        if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f')) return true;
        return false;
    }

};

#endif //LEX_JUDGE__TOOLS_H
