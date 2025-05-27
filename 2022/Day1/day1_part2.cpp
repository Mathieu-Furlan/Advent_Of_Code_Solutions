#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int first{0};
    int second{0};
    int third{0};
    int elfCalories{0};
    while(getline(file, s)){
        if(s[0] > 10){
            elfCalories += stoi(s);
        }
        else{
            std::cout << elfCalories << "\n";
            if(elfCalories > first){
                third = second;
                second = first;
                first = elfCalories;
            }
            else if(elfCalories > second){
                third = second;
                second = elfCalories;
            }
            else if(elfCalories > third){
                third = elfCalories;
            }
            elfCalories = 0;
        }
    }
    std::cout << elfCalories << "\n";
    if(elfCalories > first){
        third = second;
        second = first;
        first = elfCalories;
    }
    else if(elfCalories > second){
        third = second;
        second = elfCalories;
    }
    else if(elfCalories > third){
        third = elfCalories;
    }
    int res{first + second + third};
    std::cout << res << "\n";
    return res;
}