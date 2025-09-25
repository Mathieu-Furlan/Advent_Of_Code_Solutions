#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

int main(){
    std::ifstream file("inputtest2");
    std::string s;
    std::vector<long> listCode;
    std::string value;
    std::unordered_map<int, long> additionalMemory;
    while(getline(file, s)){
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58 || s[i] == '-'){
                value += s[i];
            }
            else if(s[i] == ','){
                listCode.push_back(std::stol(value));
                value.clear();
            }
        }
    }
    listCode.push_back(std::stol(value));
    int opCode;
    int relativeBase{0};
    for(int i = 0; i <= listCode.size() - 1; i++){
        std::cout << relativeBase << "\n";
        long firstPos;
        long secondPos;
        long thirdPos;
        std::vector<char> parameters;
        if(listCode[i] < 100){
            opCode = listCode[i];
        }
        else{
            opCode = listCode[i] % 100;
            std::string paramSetup{std::to_string(listCode[i])};
            for(int i = paramSetup.length() - 1 - 2; i >= 0; i--){
                parameters.push_back(paramSetup[i]);
            }
        }
        if(opCode == 99){
            break;
        }
        else if(opCode == 1 || opCode == 2 || opCode == 4 || opCode == 5 || opCode == 6 || opCode == 8 || opCode == 9){
            if(parameters.size() == 0 || parameters[0] == '0'){
                if(listCode[listCode[i + 1]] >= listCode.size()){
                    if(additionalMemory.find(listCode[listCode[i + 1]]) != additionalMemory.end()){
                        firstPos = additionalMemory.at(listCode[listCode[i + 1]]);
                    }
                    else{
                        additionalMemory.insert(std::make_pair(listCode[listCode[i + 1]], 0));
                        firstPos = 0;
                    }
                }
                else firstPos = listCode[listCode[i + 1]];
            }
            else if(parameters[0] == '2'){
                if(listCode[i + 1] + relativeBase <= listCode.size() - 1){
                    firstPos = listCode[listCode[i + 1] + relativeBase];
                }
                else if(additionalMemory.find(listCode[i + 1] + relativeBase) == additionalMemory.end()){
                    additionalMemory.insert(std::make_pair(listCode[i + 1] + relativeBase, 0));
                    firstPos = 0;
                }
                else if(additionalMemory.find(listCode[i + 1] + relativeBase) != additionalMemory.end()){
                    firstPos = additionalMemory.at(listCode[i + 1] + relativeBase);
                }
            }
            else firstPos = listCode[i + 1];
            if(parameters.size() < 2 || (parameters.size() > 1 && parameters[1] == '0')){
                if(listCode[listCode[i + 2]] >= listCode.size()){
                    if(additionalMemory.find(listCode[listCode[i + 2]]) != additionalMemory.end()){
                        secondPos = additionalMemory.at(listCode[listCode[i + 2]]);
                    }
                    else{
                        additionalMemory.insert(std::make_pair(listCode[listCode[i + 2]], 0));
                        secondPos = 0;
                    }
                }
                else secondPos = listCode[listCode[i + 2]];
            }
            else if(parameters[1] == '2'){
                if(listCode[i + 2] + relativeBase <= listCode.size() - 1){
                    secondPos = listCode[listCode[i + 2] + relativeBase];
                }
                else if(additionalMemory.find(listCode[i + 2] + relativeBase) == additionalMemory.end()){
                    additionalMemory.insert(std::make_pair(listCode[i + 2] + relativeBase, 0));
                    secondPos = 0;
                }
                else if(additionalMemory.find(listCode[i + 2] + relativeBase) != additionalMemory.end()){
                    secondPos = additionalMemory.at(listCode[i + 2] + relativeBase);
                }
            }
            else secondPos = listCode[i + 2];
        }
        if(opCode == 1){
            if(listCode[i + 3] <= listCode.size() - 1){
                listCode[listCode[i + 3]] = firstPos + secondPos;
            }
            else if(additionalMemory.find(listCode[i + 3]) != additionalMemory.end()){
                additionalMemory.at(listCode[i + 3]) = firstPos + secondPos;
            }
            else additionalMemory.insert(std::make_pair(listCode[i + 3], firstPos + secondPos));
            i += 3;
        }
        else if(opCode == 2){
            if(listCode[i + 3] <= listCode.size() - 1){
                listCode[i + 3] = firstPos * secondPos;
            }
            else if(additionalMemory.find(listCode[i + 3]) != additionalMemory.end()){
                additionalMemory.at(listCode[i + 3]) = firstPos * secondPos;
            }
            else additionalMemory.insert(std::make_pair(listCode[i + 3], firstPos * secondPos));
            i += 3;
        }
        else if(opCode == 3){
            std::cout << "Enter ID of system to test: " << "\n";
            if(parameters.size() == 0){
                std::cin >> listCode[listCode[i + 1]];
            }
            else std::cin >> listCode[listCode[i + 1] + relativeBase];
            i++;
        }
        else if(opCode == 4){
            std::cout << firstPos << "\n";
            i++;
        }
        else if(opCode == 5){
            if(firstPos != 0){
                i = secondPos - 1;
            }
            else i += 2;
        }
        else if(opCode == 6){
            if(firstPos == 0){
                i = secondPos - 1;
            }
            else i += 2;
        }
        else if(opCode == 7){
            if(firstPos < secondPos){
                listCode[listCode[i + 3]] = 1;
            }
            else listCode[listCode[i + 3]] = 0;
            i += 3;
        }
        else if(opCode == 8){
            if(firstPos == secondPos){
                listCode[listCode[i + 3]] = 1;
            }
            else listCode[listCode[i + 3]] = 0;
            i += 3;
        }
        else if(opCode == 9){
            relativeBase += firstPos;
            i++;
        }
    }
    return 0;
}