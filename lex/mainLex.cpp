#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "judgeTool.h"

using namespace std;

void scanning(string infilename, string outfilename) {
    ifstream infile;
    judgeTool jt;
    infile.open(infilename.data());
    if (!infile.is_open()) {
        cout << "open fail!" << endl;
    }
    infile >> noskipws;

    ofstream ofile;               //定义输出文件
    ofile.open(outfilename, ios::out | ios::app);     //作为输出文件打开
    ofile << "------------------------------" << "全文扫描输出" << "---------------" << endl;

    int totalTable[34] = {0}; // 各词数量统计
    int pos = 0, total = 0, totalNote = 0; // 行数, 总字符数, 注释字符数
    string errors = ""; // 记录错误
    char ch;
    string st = "", note;
    while (infile >> ch) {
        st = "";
        if (jt.IsFilter(ch)) { // 过滤符判断
            if (ch == '\n')
                pos += 1;
            continue;
        } else if (jt.IsUpLetter(ch) || jt.IsLowLetter(ch) || ch == '_') { // 关键字和标识符判断
            while (!infile.eof() && (jt.IsUpLetter(ch) || jt.IsLowLetter(ch) || ch == '_' || jt.IsDigit(ch))) {
                st += ch;
                infile >> ch;
                total ++;
            }
            infile.putback(ch);
            if (jt.IsKeyword(st)) {
                if (st == "int") {
                    ofile << "位于第 " << pos + 1 << " 行 < 2" << " , " << st << " >" << endl;
                    totalTable[2] += 1;
                } else if (st == "while") {
                    ofile << "位于第 " << pos + 1 << " 行 < 3" << " , " << st << " >" << endl;
                    totalTable[3] += 1;
                } else if (st == "if") {
                    ofile << "位于第 " << pos + 1 << " 行 < 4" << " , " << st << " >" << endl;
                    totalTable[4] += 1;
                } else if (st == "else") {
                    ofile << "位于第 " << pos + 1 << " 行 < 5" << " , " << st << " >" << endl;
                    totalTable[5] += 1;
                } else if (st == "get") {
                    ofile << "位于第 " << pos + 1 << " 行 < 6" << " , " << st << " >" << endl;
                    totalTable[6] += 1;
                } else if (st == "put") {
                    ofile << "位于第 " << pos + 1 << " 行 < 7" << " , " << st << " >" << endl;
                    totalTable[7] += 1;
                }
            } else {
                ofile << "位于第 " << pos + 1 << " 行 < 1" << " , letter >" << " 变量名为：" << st << endl;
                totalTable[1] += 1;
            }
        } else if (jt.IsDigit(ch)) { // 数字判断
            int judgeError = 0, judge8 = 0, judge16 = 0;

            st += ch;
            if(ch == '0'){
                infile >> ch;
                total ++;
                if(jt.IsDigit(ch))
                    judge8 = 1;
                else if(ch == 'x' || ch == 'X')
                    judge16 = 1;
            }else{
                infile >> ch;
            }

            if(judge8 == 1){
                while (!infile.eof() && jt.IsEnd(ch)) {
                    if(!jt.IsDigit8(ch))
                        judgeError = 1;
                    st += ch;
                    infile >> ch;
                    total ++;
                }
            }else if(judge16 == 1){
                while (!infile.eof() && jt.IsEnd(ch)) {
                    if(!jt.IsDigit16(ch))
                        judgeError = 1;
                    st += ch;
                    infile >> ch;
                    total ++;
                }
            }else{
                while (!infile.eof() && jt.IsEnd(ch)) {
                    if(!jt.IsDigit(ch))
                        judgeError = 1;
                    st += ch;
                    infile >> ch;
                    total ++;
                }
            }
            infile.putback(ch);
            if(judgeError){
                ofile << "ERROR!!!!!!!位于第 " << pos + 1 << " 行 出现拼写错误, 错误内容为 " << st << endl;
                errors = errors + "ERROR!!!!!!!位于第 " + to_string(pos + 1) + " 行 出现拼写错误, 错误内容为 " + st + "\n";
            }else{
                ofile << "位于第 " << pos + 1 << " 行 < 0" << " , digit >" << "数字为" << st << endl;
                totalTable[0] += 1;
            }

        } else { // 其余符号判断
            switch (ch) {
                case '&': {
                    st += ch;
                    infile >> ch;
                    total ++;
                    if (ch == '&') {
                        st += ch;
                        ofile << "位于第 " << pos + 1 << " 行 < 19" << " , " << st << " >" << endl;
                        totalTable[19] += 1;
                    } else {
                        ofile << "位于第 " << pos + 1 << " 行 < 20" << " , " << st << " >" << endl;
                        totalTable[20] += 1;
                        infile.putback(ch);
                    }
                    break;
                }
                case '|': {
                    st += ch;
                    infile >> ch;
                    total ++;
                    if (ch == '|') {
                        st += ch;
                        ofile << "位于第 " << pos + 1 << " 行 < 21" << " , " << st << " >" << endl;
                        totalTable[21] += 1;
                    } else {
                        ofile << "位于第 " << pos + 1 << " 行 < 22" << " , " << st << " >" << endl;
                        totalTable[21] += 1;
                        infile.putback(ch);
                    }
                    break;
                }
                case '>': {
                    st += ch;
                    infile >> ch;
                    total ++;
                    if (ch == '=') {
                        st += ch;
                        ofile << "位于第 " << pos + 1 << " 行 < 16" << " , " << st << " >" << endl;
                        totalTable[16] += 1;
                    } else {
                        ofile << "位于第 " << pos + 1 << " 行 < 15" << " , " << st << " >" << endl;
                        totalTable[15] += 1;
                        infile.putback(ch);
                    }
                    break;
                }
                case '<': {
                    st += ch;
                    infile >> ch;
                    total ++;
                    if (ch == '=') {
                        st += ch;
                        ofile << "位于第 " << pos + 1 << " 行 < 18" << " , " << st << " >" << endl;
                        totalTable[18] += 1;
                    } else if (ch == '>') {
                        st += ch;
                        ofile << "位于第 " << pos + 1 << " 行 < 14" << " , " << st << " >" << endl;
                        totalTable[14] += 1;
                    } else {
                        ofile << "位于第 " << pos + 1 << " 行 < 17" << " , " << st << " >" << endl;
                        totalTable[17] += 1;
                        infile.putback(ch);
                    }
                    break;
                }
                case '=': {
                    st += ch;
                    infile >> ch;
                    total ++;
                    if (ch == '=') {
                        st += ch;
                        ofile << "位于第 " << pos + 1 << " 行 < 13" << " , " << st << " >" << endl;
                        totalTable[13] += 1;
                    } else {
                        ofile << "位于第 " << pos + 1 << " 行 < 12" << " , " << st << " >" << endl;
                        totalTable[12] += 1;
                        infile.putback(ch);
                    }
                    break;
                }
                case '+': {
                    st += ch;
                    ofile << "位于第 " << pos + 1 << " 行 < 8" << " , " << st << " >" << endl;
                    totalTable[8] += 1;
                    break;
                }
                case '-': {
                    st += ch;
                    ofile << "位于第 " << pos + 1 << " 行 < 9" << " , " << st << " >" << endl;
                    totalTable[9] += 1;
                    break;
                }
                case '*': {
                    st += ch;
                    ofile << "位于第 " << pos + 1 << " 行 < 10" << " , " << st << " >" << endl;
                    totalTable[10] += 1;
                    break;
                }
                case '!': {
                    st += ch;
                    infile >> ch;
                    total ++;
                    if (ch == '=') {
                        st += ch;
                        ofile << "位于第 " << pos + 1 << " 行 < 24" << " , " << st << " >" << endl;
                        totalTable[24] += 1;
                    } else {
                        ofile << "位于第 " << pos + 1 << " 行 < 23" << " , " << st << " >" << endl;
                        totalTable[23] += 1;
                        infile.putback(ch);
                    }
                    break;
                }
                case '/': {
                    st += ch;
                    infile >> ch;
                    total ++;
                    if (ch == '/') {
                        st += ch;
                        getline(infile, note);
                        totalNote += note.size();
                        ofile << "位于第 " << pos + 1 << " 行 < 31" << " , " << st << " >" << endl;
                        pos += 1;
                        totalTable[31] += 1;
                    } else if (ch == '*') {
                        st += ch;
                        ofile << "位于第 " << pos + 1 << " 行 < 32" << " , " << st << " >" << endl;
                        totalTable[32] += 1;
                        while (!infile.eof()) {
                            st = "";
                            infile >> ch;
                            totalNote ++;
                            total ++;
                            if(ch == '\n')
                                pos ++;
                            else if(ch == '*'){
                                st += ch;
                                infile >> ch;
                                total ++;
                                if (ch == '/') {
                                    st += ch;
                                    ofile << "位于第 " << pos + 1 << " 行 < 33" << " , " << st << " >" << endl;
                                    totalTable[33] += 1;
                                    break;
                                }
                            }
                        }
                    } else {
                        ofile << "位于第 " << pos + 1 << " 行 < 11" << " , " << st << " >" << endl;
                        totalTable[11] += 1;
                        infile.putback(ch);
                    }
                    break;
                }
                case ';': {
                    st += ch;
                    ofile << "位于第 " << pos + 1 << " 行 < 25" << " , " << st << " >" << endl;
                    totalTable[25] += 1;
                    break;
                }
                case ',': {
                    st += ch;
                    ofile << "位于第 " << pos + 1 << " 行 < 26" << " , " << st << " >" << endl;
                    totalTable[26] += 1;
                    break;
                }
                case '(': {
                    st += ch;
                    ofile << "位于第 " << pos + 1 << " 行 < 30" << " , " << st << " >" << endl;
                    totalTable[29] += 1;
                    break;
                }
                case ')': {
                    st += ch;
                    ofile << "位于第 " << pos + 1 << " 行 < 30" << " , " << st << " >" << endl;
                    totalTable[30] += 1;
                    break;
                }
                case '{': {
                    st += ch;
                    ofile << "位于第 " << pos + 1 << " 行 < 27" << " , " << st << " >" << endl;
                    totalTable[27] += 1;
                    break;
                }
                case '}': {
                    st += ch;
                    ofile << "位于第 " << pos + 1 << " 行 < 28" << " , " << st << " >" << endl;
                    totalTable[28] += 1;
                    break;
                }
                default :{
                    ofile << "ERROR!!!!!!!位于第 " << pos + 1 << " 行" "\"" << ch << "\": 无法识别的字符" << endl;
                    errors = errors + "ERROR!!!!!!!位于第 " + to_string(pos + 1) + " 行" "\"" + ch + "\": 无法识别的字符" + "\n";
                }

            }
        }
    }

    ofile << "------------------------------" << "各词数量统计" << "---------------" << endl;
    for (int i = 0; i < 34; i++) {
        ofile << "< " << i << " , " << jt.t.TOTAL[i] << " >" << "共出现了 " << totalTable[i] << " 次" << endl;
    }

    ofile << "------------------------------" << "总行数统计" << "---------------" << endl;
    ofile << "总行数为 " << pos + 1 << endl;


    ofile << "------------------------------" << "总字符数统计(不包括注释)" << "---------------" << endl;
    ofile << "总字符数(不包括注释)为 " << total << endl;

    ofile << "------------------------------" << "注释总字符数统计" << "---------------" << endl;
    ofile << "注释总字符数为 " << totalNote << endl;

    ofile << "------------------------------" << "错误统计" << "---------------" << endl;
    ofile << errors << endl;

    ofile.close();
    infile.close();
}

int main() {
    string infilename = "./test3.txt";   // 读入的绝对路径
    string outfilename = "./out3.txt";   // 写出的绝对路径

    scanning(infilename, outfilename);
    cout << "success!" << endl;

    return 0;
}
