#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <queue>

// 2541 too low
int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<int, std::unordered_map<int, std::vector<int>>> grid;
    int maxX{0};
    int maxY{0};
    int maxZ{0};
    while(getline(file, s)){
        bool firstComma{false};
        bool secondComma{false};
        std::string xVal;
        std::string yVal;
        std::string zVal;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == ','){
                if(!firstComma){
                    firstComma = true;
                }
                else secondComma = true;
            }
            else if(s[i] > 47 && s[i] < 58){
                if(!firstComma){
                    xVal += s[i];
                }
                else if(!secondComma){
                    yVal += s[i];
                }
                else zVal += s[i];
            }
        }
        int xDroplet{std::stoi(xVal)};
        maxX = std::max(maxX, xDroplet);
        int yDroplet{std::stoi(yVal)};
        maxY = std::max(maxY, yDroplet);
        int zDroplet{std::stoi(zVal)};
        maxZ = std::max(maxZ, zDroplet);
        if(grid.find(zDroplet) == grid.end()){
            std::unordered_map<int, std::vector<int>> tempMap;
            std::vector<int> tempVec;
            tempVec.push_back(yDroplet);
            tempMap.insert(std::make_pair(xDroplet, tempVec));
            grid.insert(std::make_pair(zDroplet, tempMap));
        }
        else if(grid.at(zDroplet).find(xDroplet) == grid.at(zDroplet).end()){
            std::vector<int> tempVec;
            tempVec.push_back(yDroplet);
            grid.at(zDroplet).insert(std::make_pair(xDroplet, tempVec));
        }
        else grid.at(zDroplet).at(xDroplet).push_back(yDroplet);
    }
    maxX++;
    maxY++;
    maxZ++;
    std::cout << "maxZ " << maxZ << "\n";
    std::cout << "maxX " << maxX << "\n";
    std::cout << "maxY " << maxY << "\n";
    std::vector<std::vector<std::vector<int>>> visited(maxZ + 1);
    for(int i = 0; i <= maxZ; i++){
        std::vector<std::vector<int>> xAxis(maxX + 1);
        for(int j = 0; j <= maxX; j++){
            std::vector<int> yAxis(maxY);
            std::fill(yAxis.begin(), yAxis.end(), 0);
            xAxis[j] = yAxis;
        }
        visited[i] = xAxis;
    }
    std::vector<std::vector<std::vector<int>>> dropletsLocation(maxZ + 1);
    for(int i = 0; i <= maxZ; i++){
        std::vector<std::vector<int>> xAxis(maxX + 1);
        for(int j = 0; j <= maxX; j++){
            std::vector<int> yAxis(maxY);
            std::fill(yAxis.begin(), yAxis.end(), 0);
            xAxis[j] = yAxis;
        }
        dropletsLocation[i] = xAxis;
    }
    for(auto& [key, val] : grid){
        for(auto& [droplet, cubes] : val){
            for(int i = 0; i < cubes.size(); i++){
                dropletsLocation[key][droplet][cubes[i]] = 1;
                std::cout << "location " << key << ' ' << droplet << ' ' << i << "\n";
            }
        }
    }
    int res{0};
    std::queue<std::array<int, 3>> bfsQueue;
    bfsQueue.push({0, 0, 0});
    while(bfsQueue.size() > 0){
        unsigned long level{bfsQueue.size()};
        while(level > 0){
            std::array<int, 3> current{bfsQueue.front()};
            std::cout << current[0] << ' ' << current[1] << ' ' << current[2] << "\n";
            bfsQueue.pop();
            if(current[0] > 0 && dropletsLocation[current[0] - 1][current[1]][current[2]]){
                res++;
            }
            if(current[0] < maxZ && dropletsLocation[current[0] + 1][current[1]][current[2]]){
                res++;
            }
            if(current[1] > 0 && dropletsLocation[current[0]][current[1] - 1][current[2]]){
                res++;
            }
            if(current[1] < maxX && dropletsLocation[current[0]][current[1] + 1][current[2]]){
                res++;
            }
            if(current[2] > 0 && dropletsLocation[current[0]][current[1]][current[2] - 1]){
                res++;
            }
            if(current[2] < maxY && dropletsLocation[current[0]][current[1]][current[2] + 1]){
                res++;
            }
            if(current[0] > 0 && !visited[current[0] - 1][current[1]][current[2]] && !dropletsLocation[current[0] - 1][current[1]][current[2]]){
                visited[current[0] - 1][current[1]][current[2]] = 1;
                bfsQueue.push({current[0] - 1, current[1], current[2]});
            }
            if(current[0] < maxZ && !visited[current[0] + 1][current[1]][current[2]] && !dropletsLocation[current[0] + 1][current[1]][current[2]]){
                visited[current[0] + 1][current[1]][current[2]] = 1;
                bfsQueue.push({current[0] + 1, current[1], current[2]});
            }
            if(current[1] > 0 && !visited[current[0]][current[1] - 1][current[2]] && !dropletsLocation[current[0]][current[1] - 1][current[2]]){
                visited[current[0]][current[1] - 1][current[2]] = 1;
                bfsQueue.push({current[0], current[1] - 1, current[2]});
            }
            if(current[1] < maxX && !visited[current[0]][current[1] + 1][current[2]] && !dropletsLocation[current[0]][current[1] + 1][current[2]]){
                visited[current[0]][current[1] + 1][current[2]] = 1;
                bfsQueue.push({current[0], current[1] + 1, current[2]});
            }
            if(current[2] > 0 && !visited[current[0]][current[1]][current[2] - 1] && !dropletsLocation[current[0]][current[1]][current[2] - 1]){
                visited[current[0]][current[1]][current[2] - 1] = 1;
                bfsQueue.push({current[0], current[1], current[2] - 1});
            }
            if(current[2] < maxY && !visited[current[0]][current[1]][current[2] + 1] && !dropletsLocation[current[0]][current[1]][current[2] + 1]){
                visited[current[0]][current[1]][current[2] + 1] = 1;
                bfsQueue.push({current[0], current[1], current[2] + 1});
            }
            level--;
        }
    }
    std::cout << res << "\n";
    return res;                 // il faut ajouter 5 au résultat car il y a 5 gouttes avec un axe à 0 dans les données et en initiant la recherche bfs à 0, 0, 0 on ne peux pas les contourner
}