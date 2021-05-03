#include <iostream>
#include <fstream>
#include "judgeTool.h"

using namespace std;

int main() {
    string infilename = "D:\\cpp\\clion\\lex\\test1.txt";
    string outfilename = "D:\\cpp\\clion\\lex\\out.txt";

    ifstream infile;
    judgeTool jt;
    infile.open(infilename.data());
    if( !infile.is_open()) {
        cout << "open fail!" << endl;
    }
    infile >> noskipws;
    char ch;
    int a = 0;
    while (!infile.eof()) {
        infile >> ch;
        a = infile.tellg();
        cout << ch;
        if(ch == '*'){
            infile.putback(ch);
        }

    }

    return 0;
}