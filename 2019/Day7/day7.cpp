#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>

int res{0};

void processPermutations(int index, std::vector<int>& listCode, std::array<int, 5>& phaseSetting){
    if(index == phaseSetting.size() - 1){
        int thrustersVal;
        int input{0};
        for(int k = 0; k <= phaseSetting.size() - 1; k++){     // à chaque étape
            int opCode;
            int output;
            bool secondInput{false};
            for(int i = 0; i <= listCode.size() - 1; i++){   // les instructions du jour 5
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
                    else if(parameters.size() == 1){
                        if(parameters[0] == '0'){
                            firstPos = listCode[listCode[i + 1]];
                        }
                        else firstPos = listCode[i + 1];
                        secondPos = listCode[listCode[i + 2]];
                    }
                    else if(parameters.size() == 2){
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
                    else if(parameters.size() == 1){
                        if(parameters[0] == '0'){
                            firstPos = listCode[listCode[i + 1]];
                        }
                        else firstPos = listCode[i + 1];
                        secondPos = listCode[listCode[i + 2]];
                    }
                    else if(parameters.size() == 2){
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
                    if(!secondInput){
                        listCode[listCode[i + 1]] = phaseSetting[k];       // à la première instruction on donne le numéro de phase
                        secondInput = true;
                    }
                    else{
                        listCode[listCode[i + 1]] = input;           // à la deuxième instruction on donne le résultat de la phase précédente ou zéro si c'est la première phase
                    }
                    i++;
                }
                else if(opCode == 4){
                    if(parameters.size() == 1 && parameters[0] == '1'){
                        output = listCode[i + 1];
                    }
                    else output = listCode[listCode[i + 1]];
                    std::cout << output << "\n";
                    i++;
                }
                else if(opCode == 5 || opCode == 6){
                    int firstPos;
                    int secondPos;
                    if(parameters.size() == 0){
                        firstPos = listCode[listCode[i + 1]];
                        secondPos = listCode[listCode[i + 2]];
                    }
                    else if(parameters.size() == 1){
                        if(parameters[0] == '1'){
                            firstPos = listCode[i + 1];
                        }
                        else firstPos = listCode[listCode[i + 1]];
                        secondPos = listCode[listCode[i + 2]];
                    }
                    else if(parameters.size() == 2){
                        if(parameters[0] == '0'){
                            firstPos = listCode[listCode[i + 1]];
                        }
                        else firstPos = listCode[i + 1];
                        if(parameters[1] == '0'){
                            secondPos = listCode[listCode[i + 2]];
                        }
                        else secondPos = listCode[i + 2];
                    }
                    if(opCode == 5){
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
                }
                else if(opCode == 7 || opCode == 8){
                    int firstPos;
                    int secondPos;
                    if(parameters.size() == 0){
                        firstPos = listCode[listCode[i + 1]];
                        secondPos = listCode[listCode[i + 2]];
                    }
                    else if(parameters.size() == 1){
                        if(parameters[0] == '1'){
                            firstPos = listCode[i + 1];
                        }
                        else firstPos = listCode[listCode[i + 1]];
                        secondPos = listCode[listCode[i + 2]];
                    }
                    else if(parameters.size() == 2){
                        if(parameters[0] == '0'){
                            firstPos = listCode[listCode[i + 1]];
                        }
                        else firstPos = listCode[i + 1];
                        if(parameters[1] == '0'){
                            secondPos = listCode[listCode[i + 2]];
                        }
                        else secondPos = listCode[i + 2];
                    }
                    if(opCode == 7){
                        if(firstPos < secondPos){
                            listCode[listCode[i + 3]] = 1;
                        }
                        else listCode[listCode[i + 3]] = 0;
                    }
                    else if(opCode == 8){
                        if(firstPos == secondPos){
                            listCode[listCode[i + 3]] = 1;
                        }
                        else listCode[listCode[i + 3]] = 0;
                    }
                    i += 3;
                }
            }
            input = output;
            thrustersVal = output;
        }
        if(thrustersVal > res){     // si la dernière valeur obtenue est spérieure au résultat actuel
            res = thrustersVal;
        }
    }
    else if(index >= phaseSetting.size()){
        return;
    }
    for(int m = index; m <= phaseSetting.size() - 1; m++){         // génère toutes les permutations possibles du tableau
        std::swap(phaseSetting[m], phaseSetting[index]);
        processPermutations(index + 1, listCode, phaseSetting);
        std::swap(phaseSetting[m], phaseSetting[index]);
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<int> instructions;
    std::string value;
    while(getline(file, s)){
        if(s.length() > 0){
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] > 47 && s[i] < 58 || s[i] == '-'){
                    value += s[i];
                }
                else if(s[i] == ','){
                    instructions.push_back(std::stoi(value));
                    value.clear();
                }
            }
            instructions.push_back(std::stoi(value));
        }
    }
    std::array<int, 5> initialOrder{0, 1, 2, 3, 4};
    processPermutations(0, instructions, initialOrder);
    std::cout << res << "\n";
    return 0;
}