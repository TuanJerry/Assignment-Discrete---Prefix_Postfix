#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

void MathaddChar(string &result, stack<char> &operation){
    result += operation.top(); 
    result += " ";
    operation.pop();
}

void PostaddChar(string &postfix, stack<char> &logic){
    postfix += logic.top(); 
    if(logic.top() == '<') postfix += "->";
    if(logic.top() == '-') postfix += '>';
    logic.pop(); 
}

void PostStackbonus(char infix_i, stack<char> &logic, unsigned int &index){
    logic.push(infix_i);
    if(infix_i == '<') index += 2;
    if(infix_i == '-') index += 1;
}

void PreaddChar(string &prefix, stack<char> &logic){
    if(logic.top() == '<') prefix += ">-";
    else if(logic.top() == '-') prefix += '>';
    prefix += logic.top();
    logic.pop(); 
}

void PreStackbonus(string infix, stack<char> &logic, int &index){
    if(infix[index] == '>') index--;
    if(infix[index - 1] == '<') index--;
    logic.push(infix[index]);
}

string Infix2Postfix (string infix){
    string postfix = ""; bool spacebar = false;
    stack<char> math_opt; 
    for(unsigned int i = 0; i < infix.size(); i++){
        if(infix[i] >= '0' && infix[i] <= '9'){
            postfix += infix[i];
            spacebar = true;
        } else{
            if(spacebar){
                postfix += " ";
                spacebar = false;
            }
            if(math_opt.empty()) math_opt.push(infix[i]);
            else{
                if(infix[i] != ')'){
                    if(math_opt.top() == '^') {
                        if(infix[i] != '(') MathaddChar(postfix,math_opt);
                    }
                    if(!math_opt.empty() && (math_opt.top() == '*' || math_opt.top() == '/')){
                        if(infix[i] != '^' && infix[i] != '(') MathaddChar(postfix, math_opt);
                        if(infix[i] == '+' || infix[i] == '-'){
                            if(!math_opt.empty() && math_opt.top() != '(') MathaddChar(postfix, math_opt);
                        }
                        math_opt.push(infix[i]);
                    } else if (!math_opt.empty() && math_opt.top() != '(') {
                        if(infix[i] == '+' || infix[i] == '-') MathaddChar(postfix, math_opt);
                        math_opt.push(infix[i]);
                    } else math_opt.push(infix[i]);
                } else {
                    while(math_opt.top() != '(') MathaddChar(postfix, math_opt);
                    math_opt.pop();
                }
            }
        }
    }
    while(!math_opt.empty()){
        if(postfix.back() != ' ') postfix += ' ';
        MathaddChar(postfix, math_opt);
    }
    postfix.pop_back();
    return postfix;
}

string Infix2Prefix(string infix){
    string prefix = "", reverse_prefix = "";
    stack<char> math_opt;
    for(int i = infix.size() - 1; i >= 0; i--){
        if(infix[i] >= '0' && infix[i] <= '9') reverse_prefix += infix[i];
        else{
            if(reverse_prefix.size() != 0 && reverse_prefix.back() != ' ') reverse_prefix += ' ';
            if(math_opt.empty()) math_opt.push(infix[i]);
            else{
              if(infix[i] != '('){
                    if(!math_opt.empty() && math_opt.top() == '^'){
                        if(infix[i] != ')' && infix[i] != '^') {
                            while(!math_opt.empty() && math_opt.top() == '^') MathaddChar(reverse_prefix, math_opt);
                        }
                        math_opt.push(infix[i]);
                    } else if (!math_opt.empty() && (math_opt.top() == '*' || math_opt.top() == '/')) {
                        if(infix[i] != '+' && infix[i] != '-') math_opt.push(infix[i]);
                        else {
                            while (!math_opt.empty() && math_opt.top() != '+' && math_opt.top() != '-' && math_opt.top() != ')') MathaddChar(reverse_prefix, math_opt);
                            math_opt.push(infix[i]);
                        }
                    } else math_opt.push(infix[i]);
                } else {
                    while(math_opt.top() != ')') MathaddChar(reverse_prefix, math_opt);
                    math_opt.pop();
                }
            }
        }
    }
    while(!math_opt.empty()){
        if(reverse_prefix.back() != ' ') reverse_prefix += ' ';
        MathaddChar(reverse_prefix, math_opt);
    }
    for(int i = reverse_prefix.size() - 2; i >= 0; i--) prefix += reverse_prefix[i];
    return prefix;
}

string PostfixPrefixCalculator(string input){
    string result; double ans = 0;
    double num1, num2;
    stack<string> operation; stack<double> data;
    stringstream database; database << input; 
    if(input[0] >= '0' && input[0] <= '9'){
        while(!database.eof()){
            database >> result;
            if(result[0] >= '0' && result[0] <= '9') data.push((double)stoi(result));
            else {
                num2 = data.top(); data.pop();
                num1 = data.top(); data.pop();
                if(result[0] == '+') ans = num1 + num2;
                if(result[0] == '-') ans = num1 - num2;
                if(result[0] == '*') ans = num1 * num2;
                if(result[0] == '/'){
                    if(num2 == 0) return "divided-by-0 error";
                    else ans = num1 / num2;
                }
                if(result[0] == '^'){
                    if(num1 == 0) return "undefined error";
                    else ans = pow(num1, num2);
                }
                data.push(ans);
            }
        }
    } else {
        while(!database.eof()){ 
            database >> result;
            if(result[0] < '0' || result[0] > '9') operation.push(result);
            else {
                if(operation.top()[0] != '#') {
                    data.push((double)stoi(result));
                    operation.push("#");
                } else {
                    num2 = (double)stoi(result);
                    while(!operation.empty() && operation.top()[0] == '#'){
                        num1 = data.top(); data.pop();
                        operation.pop();
                        if(operation.top()[0] == '+') ans = num1 + num2;
                        if(operation.top()[0] == '-') ans = num1 - num2;
                        if(operation.top()[0] == '*') ans = num1 * num2;
                        if(operation.top()[0] == '/'){
                            if(num2 == 0) return "divided-by-0 error";
                            else ans = num1 / num2;
                        }
                        if(operation.top()[0] == '^'){
                            if(num1 == 0) return "undefined error";
                            else ans = pow(num1, num2);
                        }
                        operation.pop(); num2 = ans;
                    }
                    data.push(num2); operation.push("#");
                }
            }
        }
    }
    ans = data.top(); data.pop();
    ans = round(ans*10000)/10000;
    result = to_string(ans);
    while(result.back() == '0') {
        result.pop_back(); 
        if(result.back() == '.'){
            result.pop_back();
            break;
        }
    }
    database.str(""); database.clear();
    return result;
}

string LogicInfix2Postfix(string infix){
    string postfix = "";
    stack<char> logic;
    for(unsigned int i = 0; i < infix.size(); i++){
        if(infix[i] != '~' && infix[i] != '|' && infix[i] != '-' && infix[i] != '(' && infix[i] != ')' && infix[i] != '<' && infix[i] != '&' && infix[i] != ' ') postfix += infix[i];
        else {
            if(infix[i] == ' ') continue;
            if(logic.empty()) PostStackbonus(infix[i], logic, i);
            else {
                if(infix[i] != ')'){
                    if(logic.top() == '~') {
                        if(infix[i] != '(') PostaddChar(postfix, logic);
                    }
                    if(!logic.empty() && (logic.top() == '&' || logic.top() == '|')) {
                        if(infix[i] != '~' && infix[i] != '(') PostaddChar(postfix, logic);
                    } 
                    if(!logic.empty() && logic.top() == '-') {
                        if(infix[i] == '-' || infix[i] == '<') PostaddChar(postfix, logic);
                    } 
                    if(!logic.empty() && logic.top() == '<') {
                        if(infix[i] == '<') PostaddChar(postfix, logic);
                    } 
                    PostStackbonus(infix[i], logic, i);
                } else {
                    while(logic.top() != '(') PostaddChar(postfix, logic);
                    logic.pop();
                }
            }  
        }
    }
    while(!logic.empty()) PostaddChar(postfix, logic);
    return postfix;
}

string LogicInfix2Prefix(string infix){
    string prefix = "", reverse_prefix = "";
    stack<char> logic;
    for(int i = infix.size() - 1; i >= 0; i--){
        if(infix[i] != '~' && infix[i] != '|' && infix[i] != '(' && infix[i] != ')' && infix[i] != '>' && infix[i] != '&' && infix[i] != ' ') reverse_prefix += infix[i];
        else {
            if(infix[i] == ' ') continue;
            if(logic.empty()) PreStackbonus(infix, logic, i);
            else {
                if(infix[i] != '('){
                    if(logic.top() == '~') {
                        if(infix[i] != ')' && infix[i] != '~') {
                            while(!logic.empty() && logic.top() == '~') PreaddChar(reverse_prefix, logic);
                        }
                    }
                    if(!logic.empty() && (logic.top() == '&' || logic.top() == '|')) {
                        if(infix[i] == '>' && infix[i - 2] == '<') {
                            while(!logic.empty() && logic.top() != '<' && logic.top() != ')') PreaddChar(reverse_prefix, logic);
                        } else if(infix[i] == '>'){
                            while(!logic.empty() && logic.top() != '-' && logic.top() != ')') PreaddChar(reverse_prefix, logic);
                        }   
                    } 
                    if(!logic.empty() && logic.top() == '-') {
                        if(infix[i] == '>' && infix[i - 2] == '<') {
                            while(!logic.empty() && logic.top() != '<' && logic.top() != ')') PreaddChar(reverse_prefix, logic);
                        }
                    } 
                    PreStackbonus(infix, logic, i);
                } else {
                    while(logic.top() != ')') PreaddChar(reverse_prefix, logic);
                    logic.pop();
                }
            }  
        }
    }
    while(!logic.empty()) PreaddChar(reverse_prefix, logic);
    for(int i = reverse_prefix.size() - 1; i >= 0; i--) prefix += reverse_prefix[i];
    return prefix;
}

string LogicPostfixPrefixCalculator(string input,string varlue){
    // Replace variable with value
    unsigned int i = 0, j = 0;
    while(varlue[j] != '0' && varlue[j] != '1') j++;
    while(j < varlue.size()){
        size_t laplace = input.find(varlue[i]);
        while(laplace != string::npos){
            input[laplace] = varlue[j];
            laplace = input.find(varlue[i], laplace + 1);
        }
        i += 2; j += 2;
    }
    //Calculation
    char var1, var2, ans;
    stack<char> data;
    if(input[0] == '0' || input[0] == '1') {
        for(i = 0; i < input.size(); i++){
            if(input[i] == '0' || input[i] == '1') data.push(input[i]);
            else {
                var2 = data.top(); data.pop();
                if(input[i] == '~') {
                    if(var2 == '0') ans = '1';
                    else ans = '0';
                } else {
                    var1 = data.top(); data.pop();
                    if(input[i] == '&') {
                        if(var1 == '1' && var2 == '1') ans = '1';
                        else ans = '0';
                    }
                    if(input[i] == '|') {
                        if(var1 == '0' && var2 == '0') ans = '0';
                        else ans = '1';
                    }
                    if(input[i] == '-') {
                        if(var1 == '1' && var2 == '0') ans = '0';
                        else ans = '1';
                        i++;
                    }
                    if(input[i] == '<') {
                        if(var1 == var2) ans = '1';
                        else ans = '0';
                        i += 2;
                    }  
                }
                data.push(ans);
            }
        }
    } else {
        for(j = 0; j < input.size(); j++){
            if(input[j] != '0' && input[j] != '1') {
                data.push(input[j]);
                if(input[j] == '<') j += 2;
                else if(input[j] == '-') j++;
            } else {
                if(data.top() != '1' && data.top() != '0' && data.top() != '~') data.push(input[j]);
                else {
                    var2 = input[j];
                    while(!data.empty() && (data.top() == '0' || data.top() == '1' || data.top() == '~')){
                        if(data.top() == '~') {
                            if(var2 == '0') ans = '1';
                            else ans = '0';
                        } else {
                            var1 = data.top(); data.pop();
                            if(data.top() == '&') {
                                if(var1 == '1' && var2 == '1') ans = '1';
                                else ans = '0';
                            }
                            if(data.top() == '|') {
                                if(var1 == '0' && var2 == '0') ans = '0';
                                else ans = '1';
                            }
                            if(data.top() == '-') {
                                if(var1 == '1' && var2 == '0') ans = '0';
                                else ans = '1';
                            }
                            if(data.top() == '<') {
                                if(var1 == var2) ans = '1';
                                else ans = '0';
                            }  
                        }
                        data.pop(); var2 = ans;
                    }
                    data.push(var2);
                }
            }
        }
    }
    ans = data.top(); data.pop();
    if(ans == '1') return "TRUE";
    else return "FALSE";
}

