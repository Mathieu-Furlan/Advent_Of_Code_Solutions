#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

int main(){
    std::unordered_map<int, std::unordered_set<int>> groundLevel;
    std::ifstream file("inputtest");
    std::string s;
    int rows{0};
    int cols{0};
    std::unordered_set<int> groundCols;
    while(getline(file, s)){
        std::unordered_set<int> groundCols;
        groundLevel.insert(std::make_pair(rows, groundCols));
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == '#'){
                groundLevel.at(rows).insert(i);
            }
        }
        if(rows == 0){
            cols = s.length();
        }
        rows++;
    }
    std::unordered_map<int, std::unordered_map<int, std::unordered_set<int>>> addFirstLevel;
    addFirstLevel.insert(std::make_pair(0, groundLevel));
    std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::unordered_set<int>>>> fourDimensional;
    fourDimensional.insert(std::make_pair(0, addFirstLevel));
    int minRow{-1};
    int maxRow{rows};
    int minCol{-1};
    int maxCol{cols};
    int minLevel{0};
    int maxLevel{0};
    int minDimension{0};
    int maxDimension{0};
    int cycles{0};
    while(cycles < 6){
        minLevel--;
        maxLevel++;
        std::unordered_map<int, std::unordered_map<int, std::vector<std::array<int, 2>>>> toBeActivated;
        std::unordered_map<int, std::unordered_map<int, std::vector<std::array<int, 2>>>> toBeDeactivated;
        for(int m = minDimension; m <= maxDimension; m++){
            if(fourDimensional.find(m) == fourDimensional.end()){
                std::unordered_map<int, std::unordered_map<int, std::unordered_set<int>>> tempMap;
                fourDimensional.insert(std::make_pair(m, tempMap));
            }
            for(int k = minLevel; k <= maxLevel; k++){
                if(fourDimensional.at(m).find(k) == fourDimensional.at(m).end()){
                    std::unordered_map<int, std::unordered_set<int>> tempMap;       // il faut obligatoirement créer les niveaux
                    fourDimensional.at(m).insert(std::make_pair(k, tempMap));
                }
                for(int i = minRow; i <= maxRow; i++){
                    if(fourDimensional.at(m).at(k).find(i) == fourDimensional.at(m).at(k).end()){
                        std::unordered_set<int> tempSet;                                    // il faut obligatoirement créer les lignes
                        fourDimensional.at(m).at(k).insert(std::make_pair(i, tempSet));
                    }
                    for(int j = minCol; j <= maxCol; j++){
                        bool active{false};
                        int neighbors{0};
                        if(fourDimensional.at(m).at(k).at(i).find(j) != fourDimensional.at(m).at(k).at(i).end()){
                            active = true;
                        }
                        for(int q = m - 1; q <= m + 1; q++){
                            if(fourDimensional.find(q) != fourDimensional.end()){
                                for(int r = k - 1; r <= k + 1; r++){
                                    if(fourDimensional.at(q).find(r) != fourDimensional.at(q).end()){
                                        for(int n = i - 1; n <= i + 1; n++){
                                            if(fourDimensional.at(q).at(r).find(n) != fourDimensional.at(q).at(r).end()){
                                                for(int p = j - 1; p <= j + 1; p++){
                                                    if(fourDimensional.at(q).at(r).at(n).find(p) != fourDimensional.at(q).at(r).at(n).end() && (q != m || r != k || n != i || p != j)){
                                                        neighbors++;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(active && neighbors < 2 || neighbors > 3){
                            toBeDeactivated[m][k].push_back({i, j});
                        }
                        else if(!active && neighbors == 3){
                            toBeActivated[m][k].push_back({i, j});
                        }
                    }
                }
            }
        }
        for(auto& [key, val] : toBeActivated){
            for(auto& [levels, vals] : val){
                for(auto& rowCol : vals){
                    if(fourDimensional.find(key) != fourDimensional.end()){
                        if(fourDimensional.at(key).find(levels) != fourDimensional.at(key).end()){
                            if(fourDimensional.at(key).at(levels).find(rowCol[0]) != fourDimensional.at(key).at(levels).end()){
                                fourDimensional.at(key).at(levels).at(rowCol[0]).insert(rowCol[1]);
                            }
                            else{
                                std::unordered_set<int> tempSet;
                                tempSet.insert(rowCol[1]);
                                fourDimensional.at(key).at(levels).insert(std::make_pair(rowCol[0], tempSet));
                            }
                        }
                        else{
                            std::unordered_set<int> tempSet;
                            tempSet.insert(rowCol[1]);
                            std::unordered_map<int, std::unordered_set<int>> tempMap;
                            tempMap.insert(std::make_pair(rowCol[0], rowCol[1]));
                            fourDimensional.at(key).insert(std::make_pair(levels, tempMap));
                        }
                    }
                    else{
                        std::unordered_set<int> tempSet;
                        tempSet.insert(rowCol[1]);
                        std::unordered_map<int, std::unordered_set<int>> tempMap;
                        tempMap.insert(std::make_pair(rowCol[0], rowCol[1]));
                        std::unordered_map<int, std::unordered_map<int, std::unordered_set<int>>> secondTempMap;
                        secondTempMap.insert(std::make_pair(levels, tempMap));
                        fourDimensional.insert(std::make_pair(key, secondTempMap));
                    }
                }
            }
        }
        for(auto& [key, val] : toBeDeactivated){
            for(auto& [keys, vals] : val){
                for(auto& rowCol : vals){
                    fourDimensional.at(key).at(keys).at(rowCol[0]).erase(rowCol[1]);
                }
            }
        }
        int res{0};
        for(auto& [key, val] : fourDimensional){
            for(auto& [keys, vals] : val){
                for(auto& [nextKeys, nextVals] : vals){
                    res += nextVals.size();
                }
            }
        }
        std::cout << res << "\n";
        minRow--;                           // les lignes, colonnes et niveaux sont augmentés à chaque cycle
        maxRow++;
        minCol--;
        maxCol++;
        minDimension--;
        maxDimension++;
        cycles++;
    }
    int res{0};
    for(auto& [key, val] : fourDimensional){
        for(auto& [keys, vals] : val){
            for(auto& [nextKeys, nextVals] : vals){
                res += nextVals.size();
            }
        }
    }
    std::cout << res << "\n";
    return 0;
}