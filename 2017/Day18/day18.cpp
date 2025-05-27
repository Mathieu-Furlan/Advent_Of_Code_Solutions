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
        if(registers.find(s[4]) == registers.end()){
            registers.insert(std::make_pair(s[4], 0));
        }
        instructions.push_back(s);
    }
    int index{0};
    int recoveredFreq;
    int lastSoundPlayed;
    bool found{false};
    while(!found){
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
        else if(currInstruction[0] == 's' && currInstruction[1] == 'n'){
            lastSoundPlayed = registers.at(currInstruction[4]);
            index++;
        }
        else if(currInstruction[0] == 'a'){
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
            registers.at(currInstruction[4]) += val;
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
        }
        else if(currInstruction[0] == 'm' && currInstruction[1] == 'o'){
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
            registers.at(currInstruction[4]) %= val;
            index++;
        }
        else if(currInstruction[0] == 'r'){
            if(registers.at(currInstruction[4]) != 0){
                recoveredFreq = lastSoundPlayed;
                found = true;
                std::cout << recoveredFreq << "\n";
            }
            index++;
        }
        else if(currInstruction[0] == 'j'){
            int val;
            if(registers.at(currInstruction[4]) > 0){
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