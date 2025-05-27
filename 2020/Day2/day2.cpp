#include <fstream>
#include <string>
#include <iostream>
#include <vector>
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
        int counter{0};
        for(int j = 0; j <= password.length() - 1; j++){
            if(password[j] == toCount){
                counter++;
            }
        }
        int minValNum{std::stoi(minVal)};
        int maxValNum{std::stoi(maxVal)};
        if(counter >= minValNum && counter <= maxValNum){
            res++;
        }
    }
    std::cout << res << "\n";
    return 0;
}