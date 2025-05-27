#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<int> numbersFound;
    while(getline(file, s)){
        int currentNumber{std::stoi(s)};
        for(auto& number : numbersFound){
            if(number + currentNumber == 2020){
                std::cout << number * currentNumber << "\n";
                return 0;
            }
        }
        numbersFound.push_back(currentNumber);
    }
    return 0;
}