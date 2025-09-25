#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string toScramble{"hcdefbag"};
    std::vector<std::string> instructions;
    while(getline(file, s)){
        instructions.push_back(s);
    }
    for(int j = instructions.size() - 1; j >= 0; j--){
        std::cout << toScramble << "\n";
        if(instructions[j][0] == 's'){
            if(instructions[j][5] == 'l'){
                char letterA{instructions[j][12]};
                char letterB{instructions[j][26]};
                int indexA;
                int indexB;
                for(int i = 0; i < toScramble.length(); i++){
                    if(toScramble[i] == letterA){
                        indexA = i;
                    }
                    else if(toScramble[i] == letterB){
                        indexB = i;
                    }
                }
                std::swap(toScramble[indexA], toScramble[indexB]);
            }
            else{
                int indexA{instructions[j][14] - 48};
                int indexB{instructions[j][30] - 48};
                std::swap(toScramble[indexA], toScramble[indexB]);
            }
        }
        else if(instructions[j][0] == 'r'){
            if(instructions[j][7] == 'r'){
                int rotation{instructions[j][13] - 48};
                std::rotate(toScramble.rbegin(), toScramble.rbegin() + rotation, toScramble.rend());
            }
            else if(instructions[j][7] == 'l'){
                int rotation{instructions[j][12] - 48};
                std::rotate(toScramble.begin(), toScramble.begin() + rotation, toScramble.end());
            }
            else if(instructions[j][7] == 'b'){
                char letter{instructions[j][instructions[j].length() - 1]};
                int rotationIndex;
                for(int i = 0; i < toScramble.length(); i++){
                    if(toScramble[i] == letter){
                        rotationIndex = i;
                        break;
                    }
                }
                if(rotationIndex >= 4){
                    rotationIndex++;
                }
                rotationIndex++;
                std::rotate(toScramble.rbegin(), toScramble.rbegin() + rotationIndex % toScramble.length(), toScramble.rend());
            }
            else{
                int reverseFrom{instructions[j][18] - 48};
                int reverseTo{instructions[j][28] - 48};
                std::reverse(toScramble.begin() + reverseFrom, toScramble.begin() + reverseTo + 1);
            }
        }
        else{
            int indexToRemove{instructions[j][14] - 48};
            char toMove{toScramble[instructions[j][14] - 48]};
            int indexToAdd{instructions[j][28] - 48};
            toScramble = toScramble.substr(0, indexToRemove) + toScramble.substr(indexToRemove + 1);
            toScramble.insert(indexToAdd, 1, toMove);
        }
    }
    std::cout << toScramble << "\n";
    return 0;
}