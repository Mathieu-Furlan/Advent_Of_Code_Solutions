#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <algorithm>

int main(){
    const int ROUNDS{10};
    std::ifstream file("inputtest");
    std::string s;
    std::unordered_map<int, std::array<int, 2>> elves;
    std::unordered_map<int, std::array<int, 4>> neighboursLocation;
    int elfNumber{1};
    int rowNumber{0};
    std::unordered_map<int, std::unordered_set<int>> grid;
    while(getline(file, s)){
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '#'){
                elves.insert(std::make_pair(elfNumber, std::array<int, 2>{rowNumber, i}));
                elfNumber++;
                if(grid.find(rowNumber) != grid.end()){
                    grid.at(rowNumber).insert(i);
                }
                else grid.insert(std::make_pair(rowNumber, std::unordered_set<int>{i}));
            }
        }
        rowNumber++;
    }
    int directionIndex{0};
    for(int i = 0; i < ROUNDS; i++){
        std::unordered_map<int, std::unordered_map<int, int>> considerMoving;
        for(auto& [key, val] : elves){
            bool neighbour{false};
            std::array<int, 4> neighboursDirections{0, 0, 0, 0};                // 1 si il y a un voisin
            if(grid.find(val[0] - 1) != grid.end()){
                if(grid.at(val[0] - 1).find(val[1]) != grid.at(val[0] - 1).end()){              // nord
                    neighbour = true;
                }
                if(grid.at(val[0] - 1).find(val[1] - 1) != grid.at(val[0] - 1).end()){          // on vérifie nord-est et nord-ouest
                    neighbour = true;
                    neighboursDirections[0] = 1;
                    neighboursDirections[2] = 1;
                }
                if(grid.at(val[0] - 1).find(val[1] + 1) != grid.at(val[0] - 1).end()){
                    neighbour = true;
                    neighboursDirections[0] = 1;
                    neighboursDirections[3] = 1;
                }
            }
            if(grid.find(val[0] + 1) != grid.end()){
                if(grid.at(val[0] + 1).find(val[1]) != grid.at(val[0] + 1).end()){              // sud
                    neighbour = true;
                }
                if(grid.at(val[0] + 1).find(val[1] - 1) != grid.at(val[0] + 1).end()){          // on vérifie sud-est et sud-ouest
                    neighbour = true;
                    neighboursDirections[1] = 1;
                    neighboursDirections[2] = 1;
                }
                if(grid.at(val[0] + 1).find(val[1] + 1) != grid.at(val[0] + 1).end()){
                    neighbour = true;
                    neighboursDirections[1] = 1;
                    neighboursDirections[3] = 1;
                }
            }
            if(!neighbour){                             // est et ouest
                if(grid.at(val[0]).find(val[1] - 1) != grid.at(val[0]).end()){
                    neighbour = true;
                }
                else if(grid.at(val[0]).find(val[1] + 1) != grid.at(val[0]).end()){
                    neighbour = true;
                }
            }
            if(neighbour){
                bool directionChosen{false};
                int index{directionIndex};
                do{
                    if(neighboursDirections[index] == 0){
                        if(index == 0){
                            if(considerMoving.find())
                            considerMoving.insert(std::make_pair())
                        }
                    }
                    index = (index + 1) % 4;
                }
                while(index != directionIndex);
            }
        }
        directionIndex = (directionIndex + 1) % 4;
    }
    return 0;
}