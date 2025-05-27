#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <stack>

std::array<long, 2> parenthesis(long index, std::string& expression){
    std::stack<long> leftOperator;
    std::stack<char> operand;
    for(long i = index; i <= expression.length() - 1; i++){
        if(expression[i] == '+' || expression[i] == '*'){
            operand.push(expression[i]);
            std::cout << "recursiveOperand " << operand.top() << "\n";
        }
        else if(expression[i] == '\('){
            if(leftOperator.size() > 0 && operand.top() == '+'){
                std::array<long, 2> temp{parenthesis(i + 1, expression)};
                long leftOp{leftOperator.top()};
                leftOperator.pop();
                operand.pop();
                leftOperator.push(temp[0] + leftOp);
                i = temp[1];
            }
            else{
                std::array<long, 2> temp{parenthesis(i + 1, expression)};
                leftOperator.push(temp[0]);
                i = temp[1];
            }
        }
        else if(expression[i] > 47 && expression[i] < 58){
            if(leftOperator.size() > 0 && operand.top() == '+'){
                operand.pop();
                long leftOp = leftOperator.top();
                leftOperator.pop();
                leftOperator.push(leftOp + (expression[i] - 48));
            }
            else leftOperator.push(expression[i] - 48);
        }
        else if(expression[i] == ')'){
            while(leftOperator.size() > 1){
                long firstOp{leftOperator.top()};
                std::cout << "firstOp " << firstOp << "\n";
                leftOperator.pop();
                long secondOp{leftOperator.top()};
                std::cout << "secondOp " << secondOp << "\n";
                leftOperator.pop();
                leftOperator.push(firstOp * secondOp);
            }
            std::cout << "recursiveleftOp " << leftOperator.top() << "\n";
            return {leftOperator.top(), i};
        }
    }
    return std::array<long, 2>{0, 0};
}

int main(){
    std::ifstream file("input");
    std::string s;
    long res{0};
    while(getline(file, s)){
        std::stack<long> leftOperator;                  // on utilise un stack pour traiter les multiplications après les additions
        std::stack<char> operand;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == '+' || s[i] == '*'){
                operand.push(s[i]);
                std::cout << "operand " << operand.top() << "\n";
            }
            else if(s[i] == '\('){
                if(operand.size() > 0 && operand.top() == '+'){
                    std::array<long, 2> temp{parenthesis(i + 1, s)};
                    long leftOp{leftOperator.top()};
                    leftOperator.pop();
                    operand.pop();
                    leftOperator.push(temp[0] + leftOp);
                    std::cout << "endRec " << leftOperator.top() << "\n";
                    i = temp[1];
                }
                else{
                    std::array<long, 2> temp{parenthesis(i + 1, s)};
                    leftOperator.push(temp[0]);
                    i = temp[1];
                }
            }
            else if(s[i] > 47 && s[i] < 58){
                if(leftOperator.size() > 0 && operand.top() == '+'){
                    operand.pop();
                    long leftOp{leftOperator.top()};
                    leftOperator.pop();
                    leftOperator.push(leftOp + (s[i] - 48));
                }
                else leftOperator.push(s[i] - 48);
            }
        }
        while(leftOperator.size() > 1){                     // tant qu'il reste des multiplications
            long firstOp{leftOperator.top()};
            std::cout << "firstOp " << firstOp << "\n";
            leftOperator.pop();
            long secondOp{leftOperator.top()};
            std::cout << "secondOp " << secondOp << "\n";
            leftOperator.pop();
            leftOperator.push(firstOp * secondOp);
        }
        res += leftOperator.top();
        std::cout << "leftOp " << leftOperator.top() << "\n";
    }
    std::cout << res << "\n";
    return 0;
}