#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int sprite{1};
    int cycles{0};
    while(getline(file, s)){
        if(s[0] == 110){
            if(cycles >= sprite - 1 && cycles <= sprite + 1){
                std::cout << "#";
            }
            else std::cout << ".";
            cycles++;
            if(cycles == 40 || cycles == 80 || cycles == 120 || cycles == 160 || cycles == 200 || cycles == 240){
                std::cout << "\n";
                cycles = 0;                    // une fois en fin de ligne on réinitialise le compteur de cycles
            }
        }
        else{
            std::string value;
            for(int i = 4; i <= s.length() - 1; i++){
                if(s[i] == 45 || s[i] > 47 && s[i] < 58){
                    value.push_back(s[i]);
                }
            }
            int adder{stoi(value)};
            if(cycles >= sprite - 1 && cycles <= sprite + 1){
                std::cout << "#";
            }
            else std::cout << ".";
            cycles++;
            if(cycles == 40 || cycles == 80 || cycles == 120 || cycles == 160 || cycles == 200 || cycles == 240){
                std::cout << "\n";
                cycles = 0;
            }
            if(cycles >= sprite - 1 && cycles <= sprite + 1){
                std::cout << "#";
            }
            else std::cout << ".";
            sprite += adder;
            cycles++;
            if(cycles == 40 || cycles == 80 || cycles == 120 || cycles == 160 || cycles == 200 || cycles == 240){
                std::cout << "\n";
                cycles = 0;
            }
        }
    }
    return 0;
}