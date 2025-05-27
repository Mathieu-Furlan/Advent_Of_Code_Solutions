#include <fstream>
#include <string>
#include <iostream>
#include <stack>

int main(){
    std::ifstream file("input");
    std::string s;
    std::stack<char> stackLeft;
    std::stack<char> stackRight;
    int countPairs{0};
    int res{0};
    while(getline(file, s)){
        if(s.length() > 0){
            if(stackLeft.size() == 0){
                for(int i = s.length() - 1; i >= 0; i--){
                    stackLeft.push(s[i]);
                }
            }
            else{
                bool rightOrder{true};
                std::cout << "comparison" << "\n";
                for(int i = s.length() - 1; i >= 0; i--){
                    stackRight.push(s[i]);
                }
                countPairs++;
                while(rightOrder){
                    if(stackLeft.size() == 0){
                        if(stackRight.size() == 0){                 // si les deux stacks sont vides les lignes sont égales
                            rightOrder = false;
                        }
                        break;
                    }
                    else if(stackRight.size() == 0){
                        rightOrder = false;
                        break;
                    }
                    char left = stackLeft.top();
                    stackLeft.pop();
                    if(left > 47 && left < 58){
                        if(left == '1' && stackLeft.top() == '0'){
                            stackLeft.pop();
                            left = 58;                      // si left égal 10 on lui attribue la valeur 58 qui est celle de ':'
                        }
                    }
                    char right = stackRight.top();
                    stackRight.pop();
                    if(right > 47 && right < 58){
                        if(right == '1' && stackRight.top() == '0'){
                            stackRight.pop();
                            right = 58;                 // si right égal 10 on lui attribue la valeur 58 qui est celle de ':'
                        }
                    }
                    std::cout << "left " << left << "\n";
                    std::cout << "right " << right << "\n";
                    if(left > 47 && left <= 58 && right > 47 && right <= 58){
                        if(left > right){
                            rightOrder = false;
                            break;
                        }
                        else if(right > left){
                            break;
                        }
                    }
                    else if(right == ']' && (left == '[' || left == ',' || (left > 47 && left <= 58))){
                        rightOrder = false;
                        break;
                    }
                    else if(left == ']' && (right == '[' || right == ',' || (right > 47 && right <= 58))){
                        break;
                    }
                    else if(right == '[' && left != '['){
                        if(left == ','){
                            stackLeft.pop();
                            left = stackLeft.top();
                            stackLeft.pop();
                            stackLeft.push(']');
                            stackLeft.push(left);
                        }
                        else if(left > 47 && left <= 58){
                            stackLeft.push(']');
                            stackLeft.push(left);
                        }
                    }
                    else if(left == '[' && right != '['){
                        if(right == ','){
                            stackRight.pop();
                            right = stackRight.top();
                            stackRight.pop();
                            stackRight.push(']');
                            stackRight.push(right);
                        }
                        else if(right > 47 && right <= 58){
                            stackRight.push(']');
                            stackRight.push(right);
                        }
                    }
                }
                if(rightOrder){
                    std::cout << "rightOrder" << "\n";
                    res += countPairs;
                }
                stackLeft = std::stack<char>();                     // on réinitialise les stacks
                stackRight = std::stack<char>();
            }
        }
    }
    std::cout << res << "\n";
    return 0;
}