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
            if(s[i] > 47 && s[i] < 58 || s[i] == '-'){
                value += s[i];
            }
            else if(s[i] == ','){
                listCode.push_back(std::stoi(value));
                value.clear();
            }
        }
    }
    listCode.push_back(std::stoi(value));
    int opCode;
    for(int i = 0; i <= listCode.size() - 1; i++){
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
        else if(opCode == 1){
            int firstPos;
            int secondPos;
            if(parameters.size() == 0){
                firstPos = listCode[listCode[i + 1]];
                secondPos = listCode[listCode[i + 2]];
            }
            if(parameters.size() >= 1){                    // devrait être == et pas >=
                if(parameters[0] == '0'){
                    firstPos = listCode[listCode[i + 1]];
                }
                else firstPos = listCode[i + 1];
                secondPos = listCode[listCode[i + 2]];
            }
            if(parameters.size() == 2){
                if(parameters[0] == '0'){
                    firstPos = listCode[listCode[i + 1]];
                }
                else firstPos = listCode[i + 1];
                if(parameters[1] == '0'){
                    secondPos = listCode[listCode[i + 2]];
                }
                else secondPos = listCode[i + 2];
            }
            listCode[listCode[i + 3]] = firstPos + secondPos;
            i += 3;
        }
        else if(opCode == 2){
            int firstPos;
            int secondPos;
            if(parameters.size() == 0){
                firstPos = listCode[listCode[i + 1]];
                secondPos = listCode[listCode[i + 2]];
            }
            if(parameters.size() >= 1){                         // devrait être == et pas >=
                if(parameters[0] == '0'){
                    firstPos = listCode[listCode[i + 1]];
                }
                else firstPos = listCode[i + 1];
                secondPos = listCode[listCode[i + 2]];
            }
            if(parameters.size() == 2){
                if(parameters[0] == '0'){
                    firstPos = listCode[listCode[i + 1]];
                }
                else firstPos = listCode[i + 1];
                if(parameters[1] == '0'){
                    secondPos = listCode[listCode[i + 2]];
                }
                else secondPos = listCode[i + 2];
            }
            listCode[listCode[i + 3]] = firstPos * secondPos;
            i += 3;
        }
        else if(opCode == 3){
            std::cout << "Enter ID of system to test: " << "\n";
            std::cin >> listCode[listCode[i + 1]];
            i++;
        }
        else if(opCode == 4){
            if(parameters.size() == 1 && parameters[0] =='1'){
                std::cout << listCode[i + 1] << "\n";
            }
            else std::cout << listCode[listCode[i + 1]] << "\n";
            i++;
        }
    }
    return 0;
}