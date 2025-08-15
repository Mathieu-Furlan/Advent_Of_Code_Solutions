#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::array<std::array<int, 3>, 3> keyPad{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
    std::array<int, 2> position{1, 1};
    while(getline(file, s)){
        for(int i = 0; i < s.length(); i++){
            if(s[i] == 'U' && position[0] > 0){
                position[0]--;
            }
            else if(s[i] == 'D' && position[0] < 2){
                position[0]++;
            }
            else if(s[i] == 'L' && position[1] > 0){
                position[1]--;
            }
            else if(s[i] == 'R' && position[1] < 2){
                position[1]++;
            }
        }
        int digit{3 * position[0] + position[1] + 1};
        std::cout << digit << "\n";
    }
    return 0;
}