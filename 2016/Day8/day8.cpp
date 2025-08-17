#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::array<std::array<int, 50>, 8> screen;
    for(int i = 0; i < 8; i++){
        std::fill(screen[i].begin(), screen[i].end(), 0);
    }
    while(getline(file, s)){
        if(s[1] == 'e'){
            std::string numBuilder;
            int index{5};
            while(s[index] > 47 && s[index] < 58){
                numBuilder += s[index];
                index++;
            }
            int col{std::stoi(numBuilder)};
            numBuilder.clear();
            index++;
            while(s[index] > 47 && s[index] < 58){
                numBuilder += s[index];
                index++;
            }
            int row{std::stoi(numBuilder)};
            for(int i = 0; i < row; i++){
                for(int j = 0; j < col; j++){
                    screen[i][j] = 1;
                }
            }
        }
        else if(s[7] == 'r'){
            std::string numBuilder;
            int index{13};
            while(s[index] > 47 && s[index] < 58){
                numBuilder += s[index];
                index++;
            }
            int row{std::stoi(numBuilder)};
            numBuilder.clear();
            for(int i = index + 4; i < s.length(); i++){
                numBuilder += s[i];
            }
            int offset{std::stoi(numBuilder)};
            std::array<int, 50> temp;
            for(int i = 0; i < 50; i++){
                temp[(i + offset) % 50] = screen[row][i];
            }
            for(int i = 0; i < 50; i++){
                screen[row][i] = temp[i];
            }
        }
        else{
            std::string numBuilder;
            int index{16};
            while(s[index] > 47 && s[index] < 58){
                numBuilder += s[index];
                index++;
            }
            int col{std::stoi(numBuilder)};
            numBuilder.clear();
            for(int i = index + 4; i < s.length(); i++){
                numBuilder += s[i];
            }
            int offset{std::stoi(numBuilder)};
            std::array<int, 8> temp;
            for(int i = 0; i < 8; i++){
                temp[(i + offset) % 8] = screen[i][col];
            }
            for(int i = 0; i < 8; i++){
                screen[i][col] = temp[i];
            }
        }
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 50; j++){
                std::cout << screen[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    int res{0};
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 50; j++){
            if(screen[i][j]){
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return 0;
}