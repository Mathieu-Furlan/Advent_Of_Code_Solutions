#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <array>

int main(){
    const int ROUNDS{10};
    std::ifstream file("inputtest");
    std::string s;
    std::vector<std::string> rows;
    while(getline(file, s)){
        rows.push_back(s);
    }
    int rowNumber{0};
    std::unordered_map<int, std::vector<int>> elves;
    for(int i = rows.size() - 1; i >= 0; i--){
        for(int j = 0; j <= rows[i].length() - 1; j++){
            if(rows[i][j] == '#'){
                if(elves.find(rowNumber) != elves.end()){
                    elves.at(rowNumber).push_back(j);
                }
                else elves.insert(std::make_pair(rowNumber, std::vector<int>{j}));
            }
        }
        rowNumber++;
    }
    std::array<char, 4> directions{'N', 'S', 'W', 'E'};
    int moves{0};
    for(int i = 0;; i = (i + 1) % 4){
        std::unordered_map<int, std::vector<int>> considerMoving;
        
        moves++;
        if(moves == 10){
            break;
        }
    }
    return 0;
}