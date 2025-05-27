#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<int, std::unordered_map<int, std::vector<int>>> grid;
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
        int yDroplet{std::stoi(yVal)};
        int zDroplet{std::stoi(zVal)};
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
    int res{0};
    for(auto& [key, val] : grid){           // pour chaque étage
        for(auto& [droplet, cubes] : val){      // pour chaque ligne
            for(int i = 0; i <= cubes.size() - 1; i++){    // pour chaque colonne
                int notConnected{6};
                if(std::find(cubes.begin(), cubes.end(), cubes[i] + 1) != cubes.end()){
                    notConnected--;
                }
                if(std::find(cubes.begin(), cubes.end(), cubes[i] - 1) != cubes.end()){
                    notConnected--;
                }
                if(val.find(droplet + 1) != val.end() && std::find(val.at(droplet + 1).begin(), val.at(droplet + 1).end(), cubes[i]) != val.at(droplet + 1).end()){
                    notConnected--;
                }
                if(val.find(droplet - 1) != val.end() && std::find(val.at(droplet - 1).begin(), val.at(droplet - 1).end(), cubes[i]) != val.at(droplet - 1).end()){
                    notConnected--;
                }
                if(grid.find(key - 1) != grid.end() && grid.at(key - 1).find(droplet) != grid.at(key - 1).end() && std::find(grid.at(key - 1).at(droplet).begin(), grid.at(key - 1).at(droplet).end(), cubes[i]) != grid.at(key - 1).at(droplet).end()){
                    notConnected--;
                }
                if(grid.find(key + 1) != grid.end() && grid.at(key + 1).find(droplet) != grid.at(key + 1).end() && std::find(grid.at(key + 1).at(droplet).begin(), grid.at(key + 1).at(droplet).end(), cubes[i]) != grid.at(key + 1).at(droplet).end()){
                    notConnected--;
                }
                res += notConnected;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}