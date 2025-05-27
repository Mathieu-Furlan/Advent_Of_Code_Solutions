#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    int headCol{0};
    int headRow{0};
    int tailCol{0};
    int tailRow{0};
    std::unordered_set<std::string> visited{"00"};
    while(getline(file, s)){
        std::string moves{s[2]};
        if(s.length() == 4){
            moves += s[3];
        }
        int movements{std::stoi(moves)};
        if(s[0] == 'L'){
            while(movements > 0){
                headCol--;
                if(std::abs(tailCol - headCol) > 1){
                    tailCol = headCol + 1;
                    tailRow = headRow;
                    visited.insert(std::to_string(tailCol).append(std::to_string(tailRow)));
                }
                movements--;
            }
        }
        else if(s[0] == 'R'){
            while(movements > 0){
                headCol++;
                if(std::abs(tailCol - headCol) > 1){
                    tailCol = headCol - 1;
                    tailRow = headRow;
                    visited.insert(std::to_string(tailCol).append(std::to_string(tailRow)));
                }
                movements--;
            }
        }
        else if(s[0] == 'U'){
            while(movements > 0){
                headRow++;
                if(std::abs(tailRow - headRow) > 1){
                    tailRow = headRow - 1;
                    tailCol = headCol;
                    visited.insert(std::to_string(tailCol).append(std::to_string(tailRow)));
                }
                movements--;
            }
        }
        else if(s[0] == 'D'){
            while(movements > 0){
                headRow--;
                if(std::abs(tailRow - headRow) > 1){
                    tailRow = headRow + 1;
                    tailCol = headCol;
                    visited.insert(std::to_string(tailCol).append(std::to_string(tailRow)));
                }
                movements--;
            }
        }
    }
    for(auto& cell : visited){
        std::cout << cell << "\n";
    }
    unsigned long res{visited.size()};
    std::cout << res << "\n";
    return 0;
}