#include <iostream>
using namespace std;

#include <stack> 

void addChar(string &prefix, stack<char> &logic){
    if(logic.top() == '<') prefix += ">-";
    else if(logic.top() == '-') prefix += '>';
    prefix += logic.top();
    logic.pop(); 
}

void Stackbonus(string infix, stack<char> &logic, int &index){
    if(infix[index] == '>') index--;
    if(infix[index - 1] == '<') index--;
    logic.push(infix[index]);
}

string LogicInfix2Prefix(string infix){
    string prefix = "", reverse_prefix = "";
    stack<char> logic;
    for(int i = infix.size() - 1; i >= 0; i--){
        if(infix[i] != '~' && infix[i] != '|' && infix[i] != '(' && infix[i] != ')' && infix[i] != '>' && infix[i] != '&' && infix[i] != ' ') reverse_prefix += infix[i];
        else {
            if(infix[i] == ' ') continue;
            if(logic.empty()) Stackbonus(infix, logic, i);
            else {
                if(infix[i] != '('){
                    if(logic.top() == '~') {
                        if(infix[i] != ')' && infix[i] != '~') {
                            while(!logic.empty() && logic.top() == '~') addChar(reverse_prefix, logic);
                        }
                    }
                    if(!logic.empty() && (logic.top() == '&' || logic.top() == '|')) {
                        if(infix[i] == '>' && infix[i - 2] == '<') {
                            while(!logic.empty() && logic.top() != '<' && logic.top() != ')') addChar(reverse_prefix, logic);
                        } else if(infix[i] == '>'){
                            while(!logic.empty() && logic.top() != '-' && logic.top() != ')') addChar(reverse_prefix, logic);
                        }   
                    } 
                    if(!logic.empty() && logic.top() == '-') {
                        if(infix[i] == '>' && infix[i - 2] == '<') {
                            while(!logic.empty() && logic.top() != '<' && logic.top() != ')') addChar(reverse_prefix, logic);
                        }
                    } 
                    Stackbonus(infix, logic, i);
                } else {
                    while(logic.top() != ')') addChar(reverse_prefix, logic);
                    logic.pop();
                }
            }  
        }
    }
    while(!logic.empty()) addChar(reverse_prefix, logic);
    for(int i = reverse_prefix.size() - 1; i >= 0; i--) prefix += reverse_prefix[i];
    return prefix;
}

int main(){
    for(int i = 0; i < 100; i++){
        string infix; getline(cin, infix);
        cout << LogicInfix2Prefix(infix) << endl;
    }
    return 0;
}
