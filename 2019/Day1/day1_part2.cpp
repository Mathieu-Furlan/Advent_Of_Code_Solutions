#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    int fuel{0};
    while(getline(file, s)){
        std::string mass;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58){
                mass += s[i];
            }
        }
        double res{std::floor(std::stoi(mass) / 3) - 2};
        fuel += res;
        while(res > 0){
            res = std::floor(res / 3) - 2;
            if(res > 0){
                fuel += res;
            }
        }
    }
    std::cout << fuel << "\n";
    return fuel;
}