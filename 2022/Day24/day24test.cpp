#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <queue>

int main(){
    std::ifstream file("inputtest");
    std::string s;
    std::vector<std::vector<std::array<bool, 4>>> basin;
    while(getline(file, s)){
        if(s[2] != '#'){
            std::vector<std::array<bool, 4>> populateRow;
            for(int i = 1; i < s.length() - 1; i++){
                if(s[i] == '.'){
                    populateRow.push_back({false, false, false, false});
                }
                else if(s[i] == '^'){
                    populateRow.push_back({true, false, false, false});
                }
                else if(s[i] == '>'){
                    populateRow.push_back({false, true, false, false});
                }
                else if(s[i] == 'v'){
                    populateRow.push_back({false, false, true, false});
                }
                else if(s[i] == '<'){
                    populateRow.push_back({false, false, false, true});
                }
            }
            basin.push_back(populateRow);
        }
    }
    std::queue<std::array<int, 2>> basinPositions;
    bool searching{true};
    int res{1};
    basinPositions.push({0, 0});
    while(searching){
        for(int i = 0; i < basin.size(); i++){
            for(int j = 0; j < basin[i].size(); j++){
                for(int k = 0; k < 4; k++){
                    if(basin[i][j][k]){
                        if(k == 0){
                            if(i > 0){
                                basin[i - 1][j][k] = true;
                            }
                            else basin[basin.size() - 1][j][k] = true;
                        }
                        else if(k == 1){
                            if(j == basin[i].size() - 1){
                                basin[i][0][k] = true;
                            }
                            else basin[i][j + 1][k] = true;
                        }
                        else if(k == 2){
                            if(i < basin.size() - 1){
                                basin[i + 1][j][k] = true;
                            }
                            else basin[0][j][k] = true;
                        }
                        else if(k == 3){
                            if(j == 0){
                                basin[i][basin[i].size() - 1][k] = true;
                            }
                            else basin[i][j - 1][k] = true;
                        }
                        basin[i][j][k] = false;
                    }
                }
            }
        }
        unsigned long currentMinute{basinPositions.size()};
        while(currentMinute > 0){
            std::array<int, 2> temp{basinPositions.front()};
            std::cout << basin[temp[0]][temp[1]][1] << "\n";
            for(int i = 0; i < 4; i++){
                if(basin[temp[0]][temp[1]][i]){
                    std::cout << "pop" << "\n";
                    basinPositions.pop();                // on utilise pop seulement si un blizzard nous empêche d'attendre
                    break;
                }
            }
            std::cout << "temp0: " << temp[0] << " temp1: " << temp[1] << "\n";
            if(temp[0] == basin.size() - 1 && temp[1] == basin[0].size() - 1){
                searching = true;
                break;
            }
            bool moveUp{true};
            if(temp[0] == 0){
                moveUp = false;
            }
            else{
                for(int i = 0; i < 4; i++){
                    if(basin[temp[0] - 1][temp[1]][i]){
                        moveUp = false;
                    }
                }
            }
            if(moveUp){
                basinPositions.push({temp[0] - 1, temp[1]});
            }
            std::cout << "moveUp" << "\n";
            bool moveRight{true};
            if(temp[1] == basin[0].size() - 1){
                moveRight = false;
            }
            else{
                for(int i = 0; i < 4; i++){
                    if(basin[temp[0]][temp[1] + 1][i]){
                        moveRight = false;
                    }
                }
            }
            if(moveRight){
                basinPositions.push({temp[0], temp[1] + 1});
            }
            std::cout << "moveRight" << "\n";
            bool moveDown{true};
            if(temp[0] == basin.size() - 1){
                moveDown = false;
            }
            else{
                for(int i = 0; i < 4; i++){
                    if(basin[temp[0] + 1][temp[1]][i]){
                        moveDown = false;
                    }
                }
            }
            if(moveDown){
                basinPositions.push({temp[0] + 1, temp[1]});
            }
            std::cout << "moveDown" << "\n";
            bool moveLeft{true};
            if(temp[1] == 0){
                moveLeft = false;
            }
            else{
                for(int i = 0; i < 4; i++){
                    if(basin[temp[0]][temp[1] - 1][i]){
                        moveLeft = false;
                    }
                }
            }
            if(moveLeft){
                basinPositions.push({temp[0], temp[1] - 1});
            }
            std::cout << "moveLeft" << "\n";
            currentMinute--;
            std::cout << basinPositions.size() << "\n";
        }
        res++;
    }
    std::cout << res << "\n";
    return 0;
}