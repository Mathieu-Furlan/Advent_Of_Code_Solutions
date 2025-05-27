#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>

int followPath(int index, std::unordered_set<int> visited, int accVal, std::vector<std::string>& instructions){
    while(index < instructions.size()){
        if(visited.find(index) != visited.end()){
            return -1;
        }
        else{
            visited.insert(index);
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
                    accVal += std::stoi(value);
                }
                else accVal -= std::stoi(value);
                index++;
            }
        }
    }
    return accVal;
}

int main(){
    std::ifstream file("input");
    std::string s;
    int accumulator{0};
    std::vector<std::string> instructions;
    std::unordered_set<int> visitedIndexes;
    int lastInstruction{0};
    while(getline(file, s)){
        instructions.push_back(s);
        lastInstruction++;
    }
    bool alreadyVisited{false};
    int index{0};
    while(!alreadyVisited){
        if(visitedIndexes.find(index) != visitedIndexes.end()){
            alreadyVisited = true;
        }
        else{
            visitedIndexes.insert(index);
            if(instructions[index][0] == 'j'){
                int res{followPath(index + 1, visitedIndexes, accumulator, instructions)};  // on remplace jump par no operation
                if(res > -1){
                    std::cout << res << "\n";
                    break;
                }
                std::string value{instructions[index].substr(5)};
                if(instructions[index][4] == '+'){
                    index += std::stoi(value);
                }
                else index -= std::stoi(value);
            }
            else if(instructions[index][0] == 'n'){
                int res;
                std::string value{instructions[index].substr(5)};           // on remplace no operation par jump
                if(instructions[index][4] == '+'){
                    res = followPath(index + std::stoi(value), visitedIndexes, accumulator, instructions);
                }
                else res = followPath(index - std::stoi(value), visitedIndexes, accumulator, instructions);
                if(res > -1){
                    std::cout << res << "\n";
                    break;
                }
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