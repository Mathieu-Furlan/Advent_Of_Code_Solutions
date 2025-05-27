#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::array<char, 4> directions{'e', 'n', 'w', 's'};
    int facingDir{0};
    int row{0};
    int col{0};
    while(getline(file, s)){
        std::string value;
        for(int i = 1; i <= s.length() - 1; i++){
            value += s[i];
        }
        int move{std::stoi(value)};
        if(s[0] == 'N'){
            row += move;
        }
        else if(s[0] == 'S'){
            row -= move;
        }
        else if(s[0] == 'E'){
            col += move;
        }
        else if(s[0] == 'W'){
            col -= move;
        }
        else if(s[0] == 'L'){
            for(int i = 1; i <= move / 90; i++){
                facingDir++;
                if(facingDir == 4){
                    facingDir = 0;
                }
            }
        }
        else if(s[0] == 'R'){
            for(int i = 1; i <= move / 90; i++){
                facingDir--;
                if(facingDir == -1){
                    facingDir = 3;
                }
            }
        }
        else if(s[0] == 'F'){
            if(facingDir == 0){
                col += move;
            }
            else if(facingDir == 1){
                row += move;
            }
            else if(facingDir == 2){
                col -= move;
            }
            else if(facingDir == 3){
                row -= move;
            }
        }
    }
    std::cout << row << "\n";
    std::cout << col << "\n";
    int res{0};
    if(row < 0){
        row *= -1;
    }
    if(col < 0){
        col *= -1;
    }
    res += row + col;
    std::cout << res << "\n";
    return 0;
}