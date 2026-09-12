#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <queue>

std::vector<std::vector<std::array<bool, 4>>> blizzardsMovement(std::vector<std::vector<std::array<bool, 4>>>& grid){
    std::vector<std::vector<std::array<bool, 4>>> nextState(grid.size());
    for(int i = 0; i < grid.size(); i++){
        std::vector<std::array<bool, 4>> init(grid[0].size());
        for(int j = 0; j < grid[0].size(); j++){
            init[j] = {false, false, false, false};
        }
        nextState[i] = init;
    }
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            for(int k = 0; k < 4; k++){
                if(grid[i][j][k]){
                    if(k == 0){
                        if(i > 0){
                            nextState[i - 1][j][k] = true;
                        }
                        else nextState[grid.size() - 1][j][k] = true;
                    }
                    else if(k == 1){
                        if(j == grid[i].size() - 1){
                            nextState[i][0][k] = true;
                        }
                        else nextState[i][j + 1][k] = true;
                    }
                    else if(k == 2){
                        if(i < grid.size() - 1){
                            nextState[i + 1][j][k] = true;
                        }
                        else nextState[0][j][k] = true;
                    }
                    else if(k == 3){
                        if(j == 0){
                            nextState[i][grid[i].size() - 1][k] = true;
                        }
                        else nextState[i][j - 1][k] = true;
                    }
                }
            }
        }
    }
    return nextState;
}

int main(){
    std::ifstream file("input");
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
    for(int i = 0; i < basin.size(); i++){
        for(int j = 0; j < basin[0].size(); j++){
            for(int k = 0; k < 4; k++){
                std::cout << basin[i][j][k] << ' ';
            }
        }
        std::cout << "\n";
    }
    std::cout << "initial" << "\n";
    std::queue<std::array<int, 2>> gridPositions;
    bool searching{true};
    int res{1};
    gridPositions.push({0, 0});
    int counter{0};
    while(searching){
        basin = blizzardsMovement(basin);
        if(counter == 0){
            for(int i = 0; i < basin.size(); i++){
                for(int j = 0; j < basin[0].size(); j++){
                    for(int k = 0; k < 4; k++){
                        std::cout << basin[i][j][k] << ' ';
                    }
                }
                std::cout << "\n";
            }
        }
        counter++;
        unsigned long currentMinute{gridPositions.size()};
        while(currentMinute > 0){
            std::array<int, 2> temp{gridPositions.front()};
            gridPositions.pop();
            bool wait{true};
            for(int i = 0; i < 4; i++){
                if(basin[temp[0]][temp[1]][i]){
                    wait = false;
                }
            }
            if(wait){
                gridPositions.push({temp[0], temp[1]});
            }
            std::cout << "temp0: " << temp[0] << " temp1: " << temp[1] << "\n";
            if(temp[0] == basin.size() - 1 && temp[1] == basin[0].size() - 1){
                searching = false;
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
                gridPositions.push({temp[0] - 1, temp[1]});
            }
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
                gridPositions.push({temp[0], temp[1] + 1});
            }
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
                gridPositions.push({temp[0] + 1, temp[1]});
            }
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
                gridPositions.push({temp[0], temp[1] - 1});
            }
            currentMinute--;
            std::cout << gridPositions.size() << "\n";
        }
        res++;
    }
    std::cout << res << "\n";
    return 0;
}