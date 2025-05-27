#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::string> startingRows;
    std::unordered_map < int, std::unordered_set<int>> infected;
    int res{0};
    while(getline(file, s)){
        startingRows.push_back(s);
    }
    int reverseLign{0}; // on compte à partir de la dernière ligne pour commencer avec des coordonnées positives
    for(int i = startingRows.size() - 1; i >= 0; i--){
        std::unordered_set<int> infectedRow;
        for(int j = 0; j <= startingRows[i].length() - 1; j++){
            if(startingRows[i][j] == '#'){
                infectedRow.insert(j);
            }
        }
        infected.insert(std::make_pair(reverseLign, infectedRow));
        reverseLign++;
    }
    double nodeRow{std::floor(startingRows.size() / 2)};
    double nodeCol{std::floor(startingRows[0].length() / 2)};
    int bursts{0};
    int prevDirection{1};
    std::array<char, 4> directions{'l', 'u', 'r', 'd'};
    while(bursts < 10000){
        if(infected.find(nodeRow) == infected.end()){
            std::unordered_set<int> temp;
            infected.insert(std::make_pair(nodeRow, temp));
        }
        if(infected.at(nodeRow).find(nodeCol) != infected.at(nodeRow).end()){
            infected.at(nodeRow).erase(nodeCol);
            prevDirection++;
            if(prevDirection == 4){
                prevDirection = 0;
            }
            if(directions[prevDirection] == 'u'){
                nodeRow++;
            }
            else if(directions[prevDirection] == 'd'){
                nodeRow--;
            }
            else if(directions[prevDirection] == 'l'){
                nodeCol--;
            }
            else if(directions[prevDirection] == 'r'){
                nodeCol++;
            }
        }
        else{
            res++;
            infected.at(nodeRow).insert(nodeCol);
            prevDirection--;
            if(prevDirection == -1){
                prevDirection = 3;
            }
            if(directions[prevDirection] == 'u'){
                nodeRow++;
            }
            else if(directions[prevDirection] == 'd'){
                nodeRow--;
            }
            else if(directions[prevDirection] == 'l'){
                nodeCol--;
            }
            else if(directions[prevDirection] == 'r'){
                nodeCol++;
            }
        }
        bursts++;
    }
    std::cout << res << "\n";
    return res;
}