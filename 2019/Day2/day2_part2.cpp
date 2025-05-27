#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<int> listCode;
    std::string value;
    while(getline(file, s)){
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58){
                value += s[i];
            }
            else if(s[i] == ','){
                listCode.push_back(std::stoi(value));
                value.clear();
            }
        }
    }
    listCode.push_back(std::stoi(value));
    for(int noun = 0; noun < 100; noun++){
        listCode[1] = noun;
        for(int verb = 0; verb < 100; verb++){
            std::vector<int> copyCode = listCode;
            copyCode[2] = verb;
            for(int i = 0; i <= copyCode.size() - 1; i++){
                if(copyCode[i] == 1){
                    copyCode[copyCode[i + 3]] = copyCode[copyCode[i + 1]] + copyCode[copyCode[i + 2]];
                    i += 3;
                }
                else if(copyCode[i] == 2){
                    copyCode[copyCode[i + 3]] = copyCode[copyCode[i + 1]] * copyCode[copyCode[i + 2]];
                    i += 3;
                }
                else if(copyCode[i] == 99){
                    break;
                }
            }
            if(copyCode[0] == 19690720){
                std::cout << copyCode[1] << "\n";
                std::cout << copyCode[2] << "\n";
                std::cout << copyCode[1] * 100 + copyCode[2] << "\n";
                return 0;
            }
        }
    }
    return 0;
}