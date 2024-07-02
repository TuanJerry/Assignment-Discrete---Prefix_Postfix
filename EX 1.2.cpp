#include <iostream> 
#include <string>
#include <stack> 
using namespace std;

void addChar(string &reverse_prefix, stack<char> &math_opt){
    reverse_prefix += math_opt.top(); 
    reverse_prefix += ' ';
    math_opt.pop();
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
                            while(!math_opt.empty() && math_opt.top() == '^') addChar(reverse_prefix, math_opt);
                        }
                        math_opt.push(infix[i]);
                    } else if (!math_opt.empty() && (math_opt.top() == '*' || math_opt.top() == '/')) {
                        if(infix[i] != '+' && infix[i] != '-') math_opt.push(infix[i]);
                        else {
                            while (!math_opt.empty() && math_opt.top() != '+' && math_opt.top() != '-' && math_opt.top() != ')') addChar(reverse_prefix, math_opt);
                            math_opt.push(infix[i]);
                        }
                    } else math_opt.push(infix[i]);
                } else {
                    while(math_opt.top() != ')') addChar(reverse_prefix, math_opt);
                    math_opt.pop();
                }
            }
        }
    }
    while(!math_opt.empty()){
        if(reverse_prefix.back() != ' ') reverse_prefix += ' ';
        addChar(reverse_prefix, math_opt);
    }
    for(int i = reverse_prefix.size() - 2; i >= 0; i--) prefix += reverse_prefix[i];
    return prefix;
}

int main(){
    // for(int i = 0; i < 10; i++){
        string infix; cin >> infix;
        cout << Infix2Prefix(infix) << endl;
    //}
    return 0;
}