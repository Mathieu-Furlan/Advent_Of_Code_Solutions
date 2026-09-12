#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <algorithm>
#include <vector>

// au maximum deux elfs peuvent proposer un mouvement qui amène sur la même case
// il doivent forcément venir de directions opposées

int main(){
    int rounds{0};
    std::ifstream file("input");
    std::string s;
    std::unordered_map<int, std::unordered_set<int>> grid;
    int numberOfElves{0};
    int rowNumber{0};
    while(getline(file, s)){
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '#'){
                if(grid.find(rowNumber) != grid.end()){
                    grid.at(rowNumber).insert(i);
                }
                else grid.insert(std::make_pair(rowNumber, std::unordered_set<int>{i}));
                numberOfElves++;
            }
        }
        rowNumber++;
    }
    int directionIndex{0};
    bool moving{true};
    while(moving){
        rounds++;
        int numberOfElvesNotMoving{0};
        std::unordered_map<int, std::unordered_set<int>> considerMoving;
        for(auto& [row, col] : grid){
            for(auto& elfCol : col){
                bool neighbour{false};
                std::array<int, 4> neighboursDirections{0, 0, 0, 0};                // 1 si il y a un voisin; 0 nord, 1 sud, 2 ouest, 3 est
                if(grid.find(row - 1) != grid.end()){
                    if(grid.at(row - 1).find(elfCol) != grid.at(row - 1).end()){              // nord
                        neighbour = true;
                        neighboursDirections[0] = 1;
                    }
                    if(grid.at(row - 1).find(elfCol - 1) != grid.at(row - 1).end()){          // on vérifie nord-est et nord-ouest
                        neighbour = true;
                        neighboursDirections[0] = 1;
                        neighboursDirections[2] = 1;
                    }
                    if(grid.at(row - 1).find(elfCol + 1) != grid.at(row - 1).end()){
                        neighbour = true;
                        neighboursDirections[0] = 1;
                        neighboursDirections[3] = 1;
                    }
                }
                if(grid.find(row + 1) != grid.end()){
                    if(grid.at(row + 1).find(elfCol) != grid.at(row + 1).end()){              // sud
                        neighbour = true;
                        neighboursDirections[1] = 1;
                    }
                    if(grid.at(row + 1).find(elfCol - 1) != grid.at(row + 1).end()){          // on vérifie sud-est et sud-ouest
                        neighbour = true;
                        neighboursDirections[1] = 1;
                        neighboursDirections[2] = 1;
                    }
                    if(grid.at(row + 1).find(elfCol + 1) != grid.at(row + 1).end()){
                        neighbour = true;
                        neighboursDirections[1] = 1;
                        neighboursDirections[3] = 1;
                    }
                }
                if(grid.at(row).find(elfCol - 1) != grid.at(row).end()){       // ouest
                    neighbour = true;
                    neighboursDirections[2] = 1;
                }
                if(grid.at(row).find(elfCol + 1) != grid.at(row).end()){       // est
                    neighbour = true;
                    neighboursDirections[3] = 1;
                }
                if(neighbour){
                    int index{directionIndex};
                    bool choseDirection{false};
                    do{
                        if(neighboursDirections[index] == 0){
                            if(index == 0){
                                if(considerMoving.find(row - 1) != considerMoving.end() && considerMoving.at(row - 1).find(elfCol) != considerMoving.at(row - 1).end()){
                                    considerMoving.at(row - 1).erase(elfCol);
                                    if(considerMoving.find(row - 2) != considerMoving.end()){
                                        considerMoving.at(row - 2).insert(elfCol);
                                    }
                                    else considerMoving.insert(std::make_pair(row - 2, std::unordered_set<int>{elfCol}));
                                    if(considerMoving.find(row) != considerMoving.end()){
                                        considerMoving.at(row).insert(elfCol);
                                    }
                                    else considerMoving.insert(std::make_pair(row, std::unordered_set<int>{elfCol}));
                                }
                                else if(considerMoving.find(row - 1) != considerMoving.end()){
                                    considerMoving.at(row - 1).insert(elfCol);
                                }
                                else considerMoving.insert(std::make_pair(row - 1, std::unordered_set<int>{elfCol}));
                            }
                            else if(index == 1){
                                if(considerMoving.find(row + 1) != considerMoving.end() && considerMoving.at(row + 1).find(elfCol) != considerMoving.at(row + 1).end()){
                                    considerMoving.at(row + 1).erase(elfCol);
                                    if(considerMoving.find(row + 2) != considerMoving.end()){
                                        considerMoving.at(row + 2).insert(elfCol);
                                    }
                                    else considerMoving.insert(std::make_pair(row + 2, std::unordered_set<int>{elfCol}));
                                    if(considerMoving.find(row) != considerMoving.end()){
                                        considerMoving.at(row).insert(elfCol);
                                    }
                                    else considerMoving.insert(std::make_pair(row, std::unordered_set<int>{elfCol}));
                                }
                                else if(considerMoving.find(row + 1) != considerMoving.end()){
                                    considerMoving.at(row + 1).insert(elfCol);
                                }
                                else considerMoving.insert(std::make_pair(row + 1, std::unordered_set<int>{elfCol}));
                            }
                            else if(index == 2){
                                if(considerMoving.find(row) != considerMoving.end() && considerMoving.at(row).find(elfCol - 1) != considerMoving.at(row).end()){
                                    considerMoving.at(row).erase(elfCol - 1);
                                    considerMoving.at(row).insert(elfCol - 2);
                                    considerMoving.at(row).insert(elfCol);
                                }
                                else if(considerMoving.find(row) != considerMoving.end()){
                                    considerMoving.at(row).insert(elfCol - 1);
                                }
                                else considerMoving.insert(std::make_pair(row, std::unordered_set<int>{elfCol - 1}));
                            }
                            else{
                                if(considerMoving.find(row) != considerMoving.end() && considerMoving.at(row).find(elfCol + 1) != considerMoving.at(row).end()){
                                    considerMoving.at(row).erase(elfCol + 1);
                                    considerMoving.at(row).insert(elfCol + 2);
                                    considerMoving.at(row).insert(elfCol);
                                }
                                else if(considerMoving.find(row) != considerMoving.end()){
                                    considerMoving.at(row).insert(elfCol + 1);
                                }
                                else considerMoving.insert(std::make_pair(row, std::unordered_set<int>{elfCol + 1}));
                            }
                            choseDirection = true;
                        }
                        index = (index + 1) % 4;
                    }while(index != directionIndex && !choseDirection);
                    if(!choseDirection){                                            // si un elf a des voisins dans toutes les directions
                        if(considerMoving.find(row) != considerMoving.end()){
                            considerMoving.at(row).insert(elfCol);
                        }
                        else considerMoving.insert(std::make_pair(row, std::unordered_set<int>{elfCol}));
                        numberOfElvesNotMoving++;
                    }
                }
                else if(considerMoving.find(row) != considerMoving.end()){
                    considerMoving.at(row).insert(elfCol);
                    numberOfElvesNotMoving++;
                }
                else{
                    considerMoving.insert(std::make_pair(row, std::unordered_set<int>{elfCol}));
                    numberOfElvesNotMoving++;
                }
            }
        }
        directionIndex = (directionIndex + 1) % 4;
        grid = considerMoving;
        if(numberOfElvesNotMoving == numberOfElves){
            moving = false;
        }
    }
    std::cout << rounds << "\n";
    return 0;
}