#include <fstream>
#include <string>
#include <iostream>
#include <array>

std::array<long, 2> parenthesis(long index, std::string& expression){
    long leftOperator{-1};
    char operand;
    for(long i = index; i <= expression.length() - 1; i++){
        if(expression[i] == '+' || expression[i] == '*'){
            operand = expression[i];
        }
        else if(expression[i] == '\('){
            if(leftOperator >= 0){
                if(operand == '+'){
                    std::array<long, 2> temp{parenthesis(i + 1, expression)};
                    leftOperator += temp[0];
                    i = temp[1];
                }
                else{
                    std::array<long, 2> temp{parenthesis(i + 1, expression)};
                    leftOperator *= temp[0];
                    i = temp[1];
                }
            }
            else{
                std::array<long, 2> temp{parenthesis(i + 1, expression)};
                leftOperator = temp[0];
                i = temp[1];
            }
        }
        else if(expression[i] > 47 && expression[i] < 58){
            if(leftOperator >= 0){
                if(operand == '+'){
                    leftOperator += (expression[i] - 48);
                }
                else{
                    leftOperator *= (expression[i] - 48);
                }
            }
            else leftOperator = expression[i] - 48;
        }
        else if(expression[i] == ')'){
            return {leftOperator, i};
        }
    }
    return std::array<long, 2>{0, 0};
}

int main(){
    std::ifstream file("input");
    std::string s;
    long res{0};
    while(getline(file, s)){
        long leftOperator{-1};
        char operand;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == '+' || s[i] == '*'){
                operand = s[i];
            }
            else if(s[i] == '\('){
                if(leftOperator >= 0){
                    if(operand == '+'){
                        std::array<long, 2> temp{parenthesis(i + 1, s)};
                        leftOperator += temp[0];
                        i = temp[1];
                    }
                    else{
                        std::array<long, 2> temp{parenthesis(i + 1, s)};
                        leftOperator *= temp[0];
                        i = temp[1];
                    }
                }
                else{
                    std::array<long, 2> temp{parenthesis(i + 1, s)};
                    leftOperator = temp[0];
                    i = temp[1];
                }
            }
            else if(s[i] > 47 && s[i] < 58){
                if(leftOperator >= 0){
                    if(operand == '+'){
                        leftOperator += (s[i] - 48);
                    }
                    else{
                        leftOperator *= (s[i] - 48);
                    }
                }
                else leftOperator = s[i] - 48;
            }
        }
        res += leftOperator;
        std::cout << "leftOp " << leftOperator << "\n";
    }
    std::cout << res << "\n";
    return 0;
}