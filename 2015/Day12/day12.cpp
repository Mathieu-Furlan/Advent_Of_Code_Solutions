#include <fstream>
#include <string>
#include <iostream>

int main(){
    char ch;
    int res{0};
    std::ifstream file("input");
    std::string addNumber;
    std::string s;
    bool toAdd{false};
    bool negative{false};
    while(getline(file, s)){
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58){
                if(addNumber.length() == 0 && s[i - 1] == '-'){
                    negative = true;
                }
                addNumber += s[i];
                toAdd = true;
            }
            else if(toAdd){
                if(negative){
                    res -= std::stoi(addNumber);
                    negative = false;
                }
                else res += std::stoi(addNumber);
                addNumber.clear();
                toAdd = false;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}