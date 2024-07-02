#include <iostream>
#include "subfunc.h"
#include "subfunc.cpp"

using namespace std;

int main(){
    string math_infix, logic_infix, logic_value;
    cout << "Nhap vao infix cua bieu thuc toan: ";
    getline(cin, math_infix);
    cout << "Nhap vao infix cua bieu thuc logic: ";
    getline(cin, logic_infix);
    cout << "Nhap cac gia tri cua bien logic: ";
    getline(cin, logic_value);

    cout << "Postfix cua bieu thuc toan la: " << Infix2Postfix(math_infix) << endl;
    cout << "Prefix cua bieu thuc toan la: " << Infix2Prefix(math_infix) << endl;
    cout << "Ket qua cua bieu thuc toan theo postfix va prefix lan luot la: " 
         << PostfixPrefixCalculator(Infix2Postfix(math_infix)) << " " 
         << PostfixPrefixCalculator(Infix2Prefix(math_infix)) << endl;
    cout << "Postfix cua bieu thuc logic la: " << LogicInfix2Postfix(logic_infix) << endl;
    cout << "Prefix cua bieu thuc logic la: " << LogicInfix2Prefix(logic_infix) << endl;
    cout << "Ket qua cua bieu thuc logic theo postfix va prefix lan luot la: " 
         << LogicPostfixPrefixCalculator(LogicInfix2Postfix(logic_infix), logic_value) << " " 
         << LogicPostfixPrefixCalculator(LogicInfix2Prefix(logic_infix), logic_value) << endl;
    return 0;
}