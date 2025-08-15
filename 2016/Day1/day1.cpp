#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    getline(file, s);
    int horizontal{0};
    int vertical{0};
    int facingDir{0};                               // 0 nord, 3 est, 6 sud, 9 ouest
    for(int i = 0; i < s.length(); i++){
        if(s[i] == 'R'){
            std::string number;
            i++;
            while(s[i] >= 48 && s[i] <= 57){
                number += s[i];
                i++;
            }
            int blocks{std::stoi(number)};
            if(facingDir == 0){
                horizontal += blocks;
                facingDir = 3;
            }
            else if(facingDir == 3){
                vertical -= blocks;
                facingDir = 6;
            }
            else if(facingDir == 6){
                horizontal -= blocks;
                facingDir = 9;
            }
            else if(facingDir == 9){
                vertical += blocks;
                facingDir = 0;
            }
        }
        else if(s[i] == 'L'){
            std::string number;
            i++;
            while(s[i] >= 48 && s[i] <= 57){
                number += s[i];
                i++;
            }
            int blocks{std::stoi(number)};
            if(facingDir == 0){
                horizontal -= blocks;
                facingDir = 9;
            }
            else if(facingDir == 3){
                vertical += blocks;
                facingDir = 0;
            }
            else if(facingDir == 6){
                horizontal += blocks;
                facingDir = 3;
            }
            else if(facingDir == 9){
                vertical -= blocks;
                facingDir = 6;
            }
        }
    }
    int res{std::abs(horizontal) + std::abs(vertical)};
    std::cout << res << "\n";
    return 0;
}