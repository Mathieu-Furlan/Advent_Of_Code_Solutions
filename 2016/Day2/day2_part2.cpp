#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::array<std::array<char, 5>, 5> keyPad{{{'0', '0', '1', '0', '0'}, {'0', '2', '3', '4', '0'}, {'5', '6', '7', '8', '9'}, {'0', 'A', 'B', 'C', '0'}, {'0', '0', 'D', '0', '0'}}};
    std::array<int, 2> position{2, 0};
    std::string code;
    while(getline(file, s)){
        for(int i = 0; i < s.length(); i++){
            if(s[i] == 'U' && position[0] > 0 && keyPad[position[0] - 1][position[1]] != '0'){
                position[0]--;
            }
            else if(s[i] == 'D' && position[0] < 4 && keyPad[position[0] + 1][position[1]] != '0'){
                position[0]++;
            }
            else if(s[i] == 'L' && position[1] > 0 && keyPad[position[0]][position[1] - 1] != '0'){
                position[1]--;
            }
            else if(s[i] == 'R' && position[1] < 4 && keyPad[position[0]][position[1] + 1] != '0'){
                position[1]++;
            }
        }
        code += keyPad[position[0]][position[1]];
    }
    std::cout << code << "\n";
    return 0;
}