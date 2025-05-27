#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        std::string minVal;
        std::string maxVal;
        bool dash{false};
        char toCount;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58){
                if(dash){
                    maxVal += s[i];
                }
                else minVal += s[i];
            }
            else if(s[i] == '-'){
                dash = true;
            }
            else if(s[i] == ':'){
                toCount = s[i - 1];
                break;
            }
        }
        std::string password{s.substr(s.find(':') + 2)};
        int minValNum{std::stoi(minVal)};
        int maxValNum{std::stoi(maxVal)};
        std::cout << password[minValNum - 1] << "\n";
        std::cout << password[maxValNum - 1] << "\n";
        if(password[minValNum - 1] != password[maxValNum - 1] && (password[minValNum - 1] == toCount || password[maxValNum - 1] == toCount)){
            res++;
        }
    }
    std::cout << res << "\n";
    return 0;
}