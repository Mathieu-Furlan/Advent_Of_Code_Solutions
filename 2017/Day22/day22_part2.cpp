#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::string> startingRows;
    std::unordered_map < int, std::unordered_map<int, char>> infected;
    int res{0};
    while(getline(file, s)){
        startingRows.push_back(s);
    }
    int reverseLign{0}; // on compte à partir de la dernière ligne pour commencer avec des coordonnées positives
    for(int i = startingRows.size() - 1; i >= 0; i--){
        std::unordered_map<int, char> infectedRow;
        for(int j = 0; j <= startingRows[i].length() - 1; j++){
            if(startingRows[i][j] == '#'){
                infectedRow.insert(std::make_pair(j, '#'));
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
    while(bursts < 10000000){
        if(infected.find(nodeRow) == infected.end()){
            std::unordered_map<int, char> temp;
            infected.insert(std::make_pair(nodeRow, temp));
        }
        if(infected.at(nodeRow).find(nodeCol) != infected.at(nodeRow).end()){
            if(infected.at(nodeRow).at(nodeCol) == '#'){
                infected.at(nodeRow).at(nodeCol) = 'F';
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
            else if(infected.at(nodeRow).at(nodeCol) == 'F'){
                infected.at(nodeRow).erase(nodeCol);
                if(prevDirection == 0){
                    prevDirection = 2;
                }
                else if(prevDirection == 1){
                    prevDirection = 3;
                }
                else if(prevDirection == 2){
                    prevDirection = 0;
                }
                else if(prevDirection == 3){
                    prevDirection = 1;
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
            else if(infected.at(nodeRow).at(nodeCol) == 'W'){
                infected.at(nodeRow).at(nodeCol) = '#';
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
                res++;
            }
        }
        else{
            infected.at(nodeRow).insert(std::make_pair(nodeCol, 'W'));
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