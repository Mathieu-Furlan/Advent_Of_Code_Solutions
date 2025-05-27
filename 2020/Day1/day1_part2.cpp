#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<int> numbersFound;
    while(getline(file, s)){
        numbersFound.push_back(std::stoi(s));
    }
    for(int i = 0; i <= numbersFound.size() - 3; i++){
        for(int j = i + 1; j <= numbersFound.size() - 2; j++){
            for(int k = j + 1; k <= numbersFound.size() - 1; k++){
                if(numbersFound[i] + numbersFound[j] + numbersFound[k] == 2020){
                    std::cout << numbersFound[i] * numbersFound[j] * numbersFound[k] << "\n";
                }
            }
        }
    }
    return 0;
}