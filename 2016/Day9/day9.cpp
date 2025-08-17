#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string res;
    getline(file, s);
    for(int i = 0; i < s.length(); i++){
        if(s[i] == 40){
            int sequenceLength;
            int timesRepetion;
            std::string numBuilder;
            i++;
            while(s[i] > 47 && s[i] < 58){
                numBuilder += s[i];
                i++;
            }
            sequenceLength = std::stoi(numBuilder);
            numBuilder.clear();
            i++;
            while(s[i] > 47 && s[i] < 58){
                numBuilder += s[i];
                i++;
            }
            timesRepetion = std::stoi(numBuilder);
            i++;
            for(int j = 0; j < timesRepetion; j++){
                res += s.substr(i, sequenceLength);
            }
            i += sequenceLength - 1;
        }
        else res += s[i];
    }
    std::cout << res.length() << "\n";
    std::cout << res << "\n";
    return 0;
}