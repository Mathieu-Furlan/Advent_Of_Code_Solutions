#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::string> instructions;
    while(getline(file, s)){
        instructions.push_back(s);
    }
    int regA{1};
    int regB{0};
    int index{0};
    while(index >= 0 && index < instructions.size()){
        std::string currInstruction{instructions[index]};
        if(currInstruction[0] == 'j' && currInstruction[1] == 'm'){
            std::string value;
            int i{4};
            if(currInstruction[i] == '+'){
                i++;
            }  
            while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                value += currInstruction[i];
                i++;
            }
            index += std::stoi(value);
        }
        else if(currInstruction[0] == 'h'){
            if(currInstruction[4] == 'a'){
                regA /= 2;
            }
            else regB /= 2;
            index++;
        }
        else if(currInstruction[0] == 't'){
            if(currInstruction[4] == 'a'){
                regA *= 3;
            }
            else regB *= 3;
            index++;
        }
        else if(currInstruction[0] == 'i'){
            if(currInstruction[4] == 'a'){
                regA++;
            }
            else regB++;
            index++;
        }
        else if(currInstruction[0] == 'j' && currInstruction[1] == 'i' && currInstruction[2] == 'e'){
            std::string value;
            int i{7};
            if(currInstruction[i] == '+'){
                i++;
            }  
            while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                value += currInstruction[i];
                i++;
            }
            if(currInstruction[4] == 'a' && regA % 2 == 0){
                index += std::stoi(value);
            }
            else if(currInstruction[4] == 'b' && regB % 2 == 0){
                index += std::stoi(value);
            }
            else index++;
        }
        else if(currInstruction[0] == 'j' && currInstruction[1] == 'i' && currInstruction[2] == 'o'){
            std::string value;
            int i{7};
            if(currInstruction[i] == '+'){
                i++;
            }  
            while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                value += currInstruction[i];
                i++;
            }
            if(currInstruction[4] == 'a' && regA == 1){
                index += std::stoi(value);
            }
            else if(currInstruction[4] == 'b' && regB == 1){
                index += std::stoi(value);
            }
            else index++;
        }
    }
    std::cout << regB << "\n";
    return regB;
}