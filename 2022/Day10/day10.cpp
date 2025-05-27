#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    int signalStrength{1};
    int cycles{1};
    while(getline(file, s)){
        if(s[0] == 110){
            cycles++;
            if(cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 || cycles == 180 || cycles == 220){
                std::cout << "signal " << signalStrength << "\n";
                std::cout << cycles << " " << cycles * signalStrength << "\n";
                res += cycles * signalStrength;
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
            cycles++;
            if(cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 || cycles == 180 || cycles == 220){
                std::cout << "signal " << signalStrength << "\n";
                std::cout << cycles << " " << cycles * signalStrength << "\n";
                res += cycles * signalStrength;
            }
            signalStrength += adder;
            cycles++;
            if(cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 || cycles == 180 || cycles == 220){
                std::cout << "signal " << signalStrength << "\n";
                std::cout << cycles << " " << cycles * signalStrength  << "\n";
                res += cycles * signalStrength;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}