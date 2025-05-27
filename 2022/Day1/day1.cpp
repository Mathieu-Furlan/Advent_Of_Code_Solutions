#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    int elfCalories{0};
    while(getline(file, s)){
        if(s[0] > 10){
            elfCalories += stoi(s);
        }
        else{
            std::cout << elfCalories << "\n";
            if(elfCalories > res){
                res = elfCalories;
            }
            elfCalories = 0;
        }
    }
    std::cout << elfCalories << "\n";
    if(elfCalories > res){
        res = elfCalories;
    }
    std::cout << res << "\n";
    return res;
}