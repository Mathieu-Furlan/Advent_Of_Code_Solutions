#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

int main(){
    std::unordered_map<int, std::unordered_set<int>> groundLevel;
    std::ifstream file("input");
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
    std::unordered_map<int, std::unordered_map<int, std::unordered_set<int>>> threeDimensional;
    threeDimensional.insert(std::make_pair(0, groundLevel));
    int minRow{-1};
    int maxRow{rows};
    int minCol{-1};
    int maxCol{cols};
    int minLevel{0};
    int maxLevel{0};
    int cycles{0};
    while(cycles < 6){
        minLevel--;
        maxLevel++;
        std::unordered_map<int, std::vector<std::array<int, 2>>> toBeActivated;
        std::unordered_map<int, std::vector<std::array<int, 2>>> toBeDeactivated;
        for(int k = minLevel; k <= maxLevel; k++){
            if(threeDimensional.find(k) == threeDimensional.end()){
                std::unordered_map<int, std::unordered_set<int>> tempMap;       // il faut obligatoirement créer les niveaux
                threeDimensional.insert(std::make_pair(k, tempMap));
            }
            for(int i = minRow; i <= maxRow; i++){
                if(threeDimensional.at(k).find(i) == threeDimensional.at(k).end()){
                    std::unordered_set<int> tempSet;                                    // il faut obligatoirement créer les lignes
                    threeDimensional.at(k).insert(std::make_pair(i, tempSet));
                }
                for(int j = minCol; j <= maxCol; j++){
                    bool active{false};
                    int neighbors{0};
                    if(threeDimensional.at(k).at(i).find(j) != threeDimensional.at(k).at(i).end()){
                        active = true;                                                  // on vérifie si la cellule est active
                        std::cout << "activeLevel " << k << "\n";
                        std::cout << "activeRow " << i << "\n";
                        std::cout << "activeCol " << j << "\n";
                    }
                    for(int m = k - 1; m <= k + 1; m++){                            // on compte le nombre de cellules actives voisines
                        if(threeDimensional.find(m) != threeDimensional.end()){
                            for(int n = i - 1; n <= i + 1; n++){
                                if(threeDimensional.at(m).find(n) != threeDimensional.at(m).end()){
                                    for(int p = j - 1; p <= j + 1; p++){
                                        if(threeDimensional.at(m).at(n).find(p) != threeDimensional.at(m).at(n).end() && (m != k || n != i || p != j)){
                                            neighbors++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if(active && neighbors < 2 || neighbors > 3){
                        toBeDeactivated[k].push_back({i, j});               // toBeDeactivated[k] crée la clé k si elle n'existe pas
                    }
                    else if(!active && neighbors == 3){
                        toBeActivated[k].push_back({i, j});
                    }
                }
            }
        }
        for(auto& [key, val] : toBeActivated){                      // les cellules à activer
            for(auto& rowCol : val){
                if(threeDimensional.find(key) != threeDimensional.end()){
                    if(threeDimensional.at(key).find(rowCol[0]) != threeDimensional.at(key).end()){
                        threeDimensional.at(key).at(rowCol[0]).insert(rowCol[1]);
                    }
                    else{
                        std::unordered_set<int> tempSet;
                        tempSet.insert(rowCol[1]);
                        threeDimensional.at(key).insert(std::make_pair(rowCol[0], tempSet));
                    }
                }
                else{
                    std::unordered_set<int> tempSet;
                    tempSet.insert(rowCol[1]);
                    std::unordered_map<int, std::unordered_set<int>> tempMap;
                    tempMap.insert(std::make_pair(rowCol[0], rowCol[1]));
                    threeDimensional.insert(std::make_pair(key, tempMap));
                }
                std::cout << "activateLevel " << key << "\n";
                std::cout << "activateRow " << rowCol[0] << "\n";
                std::cout << "activateCol " << rowCol[1] << "\n";
            }
        }
        std::cout << "finalCount" << "\n";
        for(auto& [key, val] : toBeDeactivated){                    // les cellules à désactiver
            for(auto& rowCol : val){
                threeDimensional.at(key).at(rowCol[0]).erase(rowCol[1]);
            }
        }
        int res{0};
        for(auto& [key, val] : threeDimensional){
            for(auto& [keys, vals] : val){
                res += vals.size();
            }
        }
        std::cout << res << "\n";
        minRow--;                           // les lignes, colonnes et niveaux sont augmentés à chaque cycle
        maxRow++;
        minCol--;
        maxCol++;
        cycles++;
    }
    int res{0};
    for(auto& [key, val] : threeDimensional){
        for(auto& [keys, vals] : val){
            res += vals.size();
        }
    }
    std::cout << res << "\n";
    return 0;
}