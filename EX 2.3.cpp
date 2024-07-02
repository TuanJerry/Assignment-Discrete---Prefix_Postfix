#include <iostream>
#include <string>
#include <stack> 

using namespace std;

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

int main(){
    for(int i = 0; i < 2; i++){
        string infix; getline(cin, infix);
        string varlue; getline(cin, varlue);
        cout << LogicPostfixPrefixCalculator(infix , varlue) << endl;
    }
    return 0;
}