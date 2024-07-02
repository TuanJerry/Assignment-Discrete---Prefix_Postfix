#include <iostream> 
#include <string>
#include <stack> 
using namespace std;

void addChar(string &postfix, stack<char> &math_opt){
    postfix += math_opt.top(); 
    postfix += " ";
    math_opt.pop();
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
                        if(infix[i] != '(') addChar(postfix,math_opt);
                    }
                    if(!math_opt.empty() && (math_opt.top() == '*' || math_opt.top() == '/')){
                        if(infix[i] != '^' && infix[i] != '(') addChar(postfix, math_opt);
                        if(infix[i] == '+' || infix[i] == '-'){
                            if(!math_opt.empty() && math_opt.top() != '(') addChar(postfix, math_opt);
                        }
                        math_opt.push(infix[i]);
                    } else if (!math_opt.empty() && math_opt.top() != '(') {
                        if(infix[i] == '+' || infix[i] == '-') addChar(postfix, math_opt);
                        math_opt.push(infix[i]);
                    } else math_opt.push(infix[i]);
                } else {
                    while(math_opt.top() != '(') addChar(postfix, math_opt);
                    math_opt.pop();
                }
            }
        }
    }
    while(!math_opt.empty()){
        if(postfix.back() != ' ') postfix += ' ';
        addChar(postfix, math_opt);
    }
    return postfix;
}

int main(){
    string infix; cin >> infix;
    cout << Infix2Postfix(infix);
    return 0;
}