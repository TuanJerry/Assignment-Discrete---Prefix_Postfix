#include <iostream>
using namespace std;

#include <stack> 

void addChar(string &postfix, stack<char> &logic){
    postfix += logic.top(); 
    if(logic.top() == '<') postfix += "->";
    if(logic.top() == '-') postfix += '>';
    logic.pop(); 
}

void Stackbonus(char infix_i, stack<char> &logic, unsigned int &index){
    logic.push(infix_i);
    if(infix_i == '<') index += 2;
    if(infix_i == '-') index += 1;
}

string LogicInfix2Postfix(string infix){
    string postfix = "";
    stack<char> logic;
    for(unsigned int i = 0; i < infix.size(); i++){
        if(infix[i] != '~' && infix[i] != '|' && infix[i] != '-' && infix[i] != '(' && infix[i] != ')' && infix[i] != '<' && infix[i] != '&' && infix[i] != ' ') postfix += infix[i];
        else {
            if(infix[i] == ' ') continue;
            if(logic.empty()) Stackbonus(infix[i], logic, i);
            else {
                if(infix[i] != ')'){
                    if(logic.top() == '~') {
                        if(infix[i] != '(') addChar(postfix, logic);
                    }
                    if(!logic.empty() && (logic.top() == '&' || logic.top() == '|')) {
                        if(infix[i] != '~' && infix[i] != '(') addChar(postfix, logic);
                    } 
                    if(!logic.empty() && logic.top() == '-') {
                        if(infix[i] == '-' || infix[i] == '<') addChar(postfix, logic);
                    } 
                    if(!logic.empty() && logic.top() == '<') {
                        if(infix[i] == '<') addChar(postfix, logic);
                    } 
                    Stackbonus(infix[i], logic, i);
                } else {
                    while(logic.top() != '(') addChar(postfix, logic);
                    logic.pop();
                }
            }  
        }
    }
    while(!logic.empty()) addChar(postfix, logic);
    return postfix;
}

int main(){
    for(int i = 0; i < 100; i++){
        string infix; getline(cin, infix);
        cout << LogicInfix2Postfix(infix) << endl;
    }
    return 0;
}
