#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::string> packets;
    while(getline(file, s)){
        if(s.length() > 0){
            packets.push_back(s);
        }
    }
    packets.push_back("[[2]]");
    packets.push_back("[[6]]");
    std::sort(packets.begin(), packets.end(), [](const std::string& a, const std::string& b){
        std::stack<char> stackLeft;
        std::stack<char> stackRight;
        for(int i = a.length() - 1; i >= 0; i--){
            stackLeft.push(a[i]);
        }
        for(int i = b.length() - 1; i >= 0; i--){
            stackRight.push(b[i]);
        }
        while(true){
            if(stackLeft.size() == 0){
                if(stackRight.size() == 0){                 // si les deux stacks sont vides les lignes sont égales
                    return false;
                }
                return true;
            }
            else if(stackRight.size() == 0){
                return false;
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
            if(left > 47 && left <= 58 && right > 47 && right <= 58){
                if(left > right){
                    return false;
                }
                else if(right > left){
                    return true;
                }
            }
            else if(right == ']' && (left == '[' || left == ',' || (left > 47 && left <= 58))){
                return false;
            }
            else if(left == ']' && (right == '[' || right == ',' || (right > 47 && right <= 58))){
                return true;
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
    });
    int index1;
    int index2;
    for(int i = 0; i <= packets.size() - 1; i++){
        if(packets[i] == "[[2]]"){
            index1 = i + 1; 
        }
        else if(packets[i] == "[[6]]"){
            index2 = i + 1;
        }
    }
    std::cout << index1 * index2 << "\n";
    return 0;
}