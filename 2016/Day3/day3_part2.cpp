#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::array<std::array<int, 3>, 3> sides;
    int lineCounter{0};
    while(getline(file, s)){
        int triangle{0};
        for(int i = 0; i < s.length(); i++){
            if(s[i] > 47 && s[i] < 58){
                std::string numberBuilder;
                while(s[i] > 47 && s[i] < 58){
                    numberBuilder += s[i];
                    i++;
                }
                sides[triangle][lineCounter] = std::stoi(numberBuilder);
                triangle++;
            }
        }
        lineCounter++;
        if(lineCounter == 3){
            for(int i = 0; i < 3; i++){
                if(sides[i][0] < sides[i][1] + sides[i][2] && sides[i][1] < sides[i][0] + sides[i][2] && sides[i][2] < sides[i][0] + sides[i][1]){
                    res++;
                }
            }
            lineCounter = 0;
        }
    }
    std::cout << res << "\n";
    return 0;
}