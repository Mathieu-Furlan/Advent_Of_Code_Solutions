#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    int accumulator{0};
    std::vector<std::string> instructions;
    std::unordered_set<int> visitedIndexes;
    while(getline(file, s)){
        instructions.push_back(s);
    }
    bool alreadyVisited{false};
    int index{0};
    while(!alreadyVisited){
        if(visitedIndexes.find(index) != visitedIndexes.end()){
            std::cout << accumulator << "\n";
            alreadyVisited = true;
        }
        else{
            visitedIndexes.insert(index);
            if(instructions[index][0] == 'j'){
                std::string value{instructions[index].substr(5)};
                if(instructions[index][4] == '+'){
                    index += std::stoi(value);
                }
                else index -= std::stoi(value);
            }
            else if(instructions[index][0] == 'n'){
                index++;
            }
            else if(instructions[index][0] == 'a'){
                std::string value{instructions[index].substr(5)};
                if(instructions[index][4] == '+'){
                    accumulator += std::stoi(value);
                }
                else accumulator -= std::stoi(value);
                index++;
            }
        }
    }
    return 0;
}