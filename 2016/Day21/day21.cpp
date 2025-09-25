#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string toScramble{"abcdefgh"};
    while(getline(file, s)){
        std::cout << toScramble << "\n";
        if(s[0] == 's'){
            if(s[5] == 'l'){
                char letterA{s[12]};
                char letterB{s[26]};
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
                int indexA{s[14] - 48};
                int indexB{s[30] - 48};
                std::swap(toScramble[indexA], toScramble[indexB]);
            }
        }
        else if(s[0] == 'r'){
            if(s[7] == 'r'){
                int rotation{s[13] - 48};
                std::rotate(toScramble.rbegin(), toScramble.rbegin() + rotation, toScramble.rend());
            }
            else if(s[7] == 'l'){
                int rotation{s[12] - 48};
                std::rotate(toScramble.begin(), toScramble.begin() + rotation, toScramble.end());
            }
            else if(s[7] == 'b'){
                char letter{s[s.length() - 1]};
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
                int reverseFrom{s[18] - 48};
                int reverseTo{s[28] - 48};
                std::reverse(toScramble.begin() + reverseFrom, toScramble.begin() + reverseTo + 1);
            }
        }
        else{
            int indexToRemove{s[14] - 48};
            char toMove{toScramble[s[14] - 48]};
            int indexToAdd{s[28] - 48};
            toScramble = toScramble.substr(0, indexToRemove) + toScramble.substr(indexToRemove + 1);
            toScramble.insert(indexToAdd, 1, toMove);
        }
    }
    std::cout << toScramble << "\n";
    return 0;
}