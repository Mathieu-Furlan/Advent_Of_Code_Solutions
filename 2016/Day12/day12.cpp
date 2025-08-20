#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::string> instructions;
    while(getline(file, s)){
        instructions.push_back(s);
    }
    std::array<int, 4> registers;
    std::fill(registers.begin(), registers.end(), 0);
    int index{0};
    while(index < instructions.size()){
        if(instructions[index][0] == 'c'){
            int toCopy;
            if(instructions[index][4] > 96){
                toCopy = registers[instructions[index][4] - 97];
            }
            else{
                std::string numBuilder;
                for(int i = 0; i < instructions[index].length(); i++){
                    if(instructions[index][i] > 47 && instructions[index][i] < 58){
                        numBuilder += instructions[index][i];
                    }
                }
                toCopy = std::stoi(numBuilder);
            }
            registers[instructions[index][instructions[index].length() - 1] - 97] = toCopy;
            index++;
        }
        else if(instructions[index][0] == 'i'){
            registers[instructions[index][4] - 97]++;
            index++;
        }
        else if(instructions[index][0] == 'd'){
            registers[instructions[index][4] - 97]--;
            index++;
        }
        else{
            if(instructions[index][4] > 96){
                if(registers[instructions[index][4] - 97] != 0){
                    index += std::stoi(instructions[index].substr(6));
                }
                else index++;
            }
            else if(instructions[index][4] != '0'){
                index += std::stoi(instructions[index].substr(6));
            }
            else index++;
        }
    }
    std::cout << registers[0] << "\n";
    return 0;
}