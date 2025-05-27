#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::string> instructions;
    std::unordered_map<char, long long> registers;
    while(getline(file, s)){
        if(s[4] > 96 && s[4] < 123 && registers.find(s[4]) == registers.end()){
            registers.insert(std::make_pair(s[4], 0));
        }
        instructions.push_back(s);
    }
    int index{0};
    bool found{false};
    int res{0};
    while(!found){
        if(index < 0 || index >= instructions.size()){
            std::cout << res << "\n";
            return res;
        }
        std::string currInstruction{instructions[index]};
        if(currInstruction[0] == 's' && currInstruction[1] == 'e'){
            int val;
            if(currInstruction[6] > 96 && currInstruction[6] < 123){
                    val = registers.at(currInstruction[6]);
            }
            else{
                std::string value;
                int i{6};
                while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                    value += currInstruction[i];
                    i++;
                }
                val = std::stoi(value);
            }
            registers.at(currInstruction[4]) = val;
            index++;
        }
        else if(currInstruction[0] == 's' && currInstruction[1] == 'u'){
            int val;
            if(currInstruction[6] > 96 && currInstruction[6] < 123){
                val = registers.at(currInstruction[6]);
            }
            else{
                std::string value;
                int i{6};
                while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                    value += currInstruction[i];
                    i++;
                }
                val = std::stoi(value);
            }
            if(val < 0){
                registers.at(currInstruction[4]) += val * -1;
            }
            else registers.at(currInstruction[4]) -= val;
            index++;
        }
        else if(currInstruction[0] == 'm' && currInstruction[1] == 'u'){
            int val;
            if(currInstruction[6] > 96 && currInstruction[6] < 123){
                val = registers.at(currInstruction[6]);
            }
            else{
                std::string value;
                int i{6};
                while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                    value += currInstruction[i];
                    i++;
                }
                val = std::stoi(value);
            }
            registers.at(currInstruction[4]) *= val;
            index++;
            res++;
        }
        else if(currInstruction[0] == 'j'){
            int val;
            if((currInstruction[4] > 48 && currInstruction[4] < 58) || registers.at(currInstruction[4]) != 0){  // si c'est un chiffre ou une lettre
                if(currInstruction[6] > 96 && currInstruction[6] < 123){
                    val = registers.at(currInstruction[6]);
                }
                else{
                    std::string value;
                    int i{6};
                    while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                        value += currInstruction[i];
                        i++;
                    }
                    val = std::stoi(value);
                }
                index += val;
            }
            else index++;
        }
    }
    return 0;
}