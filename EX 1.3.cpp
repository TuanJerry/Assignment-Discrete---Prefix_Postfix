#include <bits/stdc++.h>
#include <stack> 
#include <sstream>

using namespace std;

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

int main(){
    string test; cin >> test;
    cout << PostfixPrefixCalculator(test);
    return 0;
}