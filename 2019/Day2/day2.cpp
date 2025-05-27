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
    listCode[1] = 12;
    listCode[2] = 2;
    int commas{0};
    int opCode;
    int firstPos;
    int secondPos;
    int outputPos;
    for(auto& code : listCode){
        if(commas == 0){
            opCode = code;
            if(opCode == 99){
                break;
            }
        }
        else if(commas == 1){
            firstPos = code;
        }
        else if(commas == 2){
            secondPos = code;
        }
        else if(commas == 3){
            outputPos = code;
            if(opCode == 1){
                listCode[outputPos] = listCode[firstPos] + listCode[secondPos];
            }
            else if(opCode == 2){
                listCode[outputPos] = listCode[firstPos] * listCode[secondPos];
            }
        }
        commas++;
        if(commas == 4){
            commas = 0;
        }
    }
    std::cout << listCode[0] << "\n";
    return 0;
}