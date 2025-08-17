#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        std::array<int, 3> sides;
        int side{0};
        for(int i = 0; i < s.length(); i++){
            if(s[i] > 47 && s[i] < 58){
                std::string numberBuilder;
                while(s[i] > 47 && s[i] < 58){
                    numberBuilder += s[i];
                    i++;
                }
                sides[side] = std::stoi(numberBuilder);
                side++;
            }
        }
        if(sides[0] < sides[1] + sides[2] && sides[1] < sides[0] + sides[2] && sides[2] < sides[0] + sides[1]){
            res++;
        }
    }
    std::cout << res << "\n";
    return 0;
}