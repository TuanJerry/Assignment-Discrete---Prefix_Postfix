#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

void MathaddChar    (string &result, stack<char> &operation);
void PreaddChar     (string &prefix, stack<char> &logic);
void PostaddChar    (string &postfix, stack<char> &logic);
void PreStackbonus  (string infix, stack<char> &logic, int &index);
void PostStackbonus (char infix_i, stack<char> &logic, unsigned int &index);

string Infix2Postfix                (string infix);
string Infix2Prefix                 (string infix);
string PostfixPrefixCalculator      (string input);
string LogicInfix2Postfix           (string infix);
string LogicInfix2Prefix            (string infix);
string LogicPostfixPrefixCalculator (string input,string varlue);
