#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

// le trajet optimal emprunte toujours le plus court chemin entre deux valves, on crée une hashMap qui contient les plus court chemins entre chaque point
// les valves cassée dont la valeur est 0 ne figurent pas dans la Map sauf AA le point de départ

int res{0};

void followPaths(int minutes, int currentValve, int cumulatedPressure, std::unordered_map<int, int>& pressureMap, std::unordered_map<int, std::unordered_map<int, int>>& mazeMap, int opened, int pressureReleased, int timeMoving){
    if(minutes == 27){
        res = std::max(res, cumulatedPressure);
        return;
    }
    cumulatedPressure += pressureReleased;
    if(timeMoving > 0){
        if(timeMoving == 1){                                    // on ajoute la pression supplémentaire lorsqu'il reste une minute de déplacement pour pouvoir continuer à se déplacer immédiatement après l'ouverture
            pressureReleased += pressureMap.at(currentValve);
        }
        followPaths(minutes + 1, currentValve, cumulatedPressure, pressureMap, mazeMap, opened, pressureReleased, timeMoving - 1);
    }
    else if(opened < 65534){                                // 65534 car il y a 15 valves qui génèrent de la pression plus AA
        for(auto& [key, val] : mazeMap.at(currentValve)){
            if(!(opened & key)){
                int nextOpen{opened | key};
                followPaths(minutes + 1, key, cumulatedPressure, pressureMap, mazeMap, nextOpen, pressureReleased, val);
            }
        }
    }
    else if(opened == 65534){                   // si on a ouvert toutes les valves
        followPaths(minutes + 1, currentValve, cumulatedPressure, pressureMap, mazeMap, opened, pressureReleased, 0);
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, int> pressure;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> pathsTo;
    std::unordered_map<int, std::unordered_map<int, int>> binaryGraph;
    std::unordered_map<int, int> binaryPressure;
    int valveNumb{2};
    std::unordered_map<std::string, int> binaryEquivalent;
    while(getline(file, s)){
        std::string valve{s.substr(6, 2)};
        std::string pathName;
        std::string value;
        value += s[23];
        if(s[24] > 47 && s[24] < 58){
            value += s[24];
        }
        for(int i = 49; i <= s.length() - 1; i++){
            if(s[i] > 64 && s[i] < 91){
                pathName += s[i];
            }
            if(s[i] == ',' || i == s.length() - 1){
                if(pathsTo.find(valve) != pathsTo.end()){
                    pathsTo.at(valve).insert(std::make_pair(pathName, 1));
                }
                else{
                    std::unordered_map<std::string, int> temp;
                    temp.insert(std::make_pair(pathName, 1));
                    pathsTo.insert(std::make_pair(valve, temp));
                }
                pathName.clear();
            }
        }
        if(value != "0" || valve == "AA"){              // AA est à 0 mais c'est le point de départ
            pressure.insert(std::make_pair(valve, std::stoi(value)));
            if(valve != "AA"){
                binaryEquivalent.insert(std::make_pair(valve, valveNumb));
                binaryPressure.insert(std::make_pair(valveNumb, std::stoi(value)));
                valveNumb <<= 1;
            }
        }
    }
    binaryEquivalent.insert(std::make_pair("AA", 1));
    binaryPressure.insert(std::make_pair(1, 0));
    std::queue<std::string> shortestPath;           // on utilise le BFS pour créer la hashMap des plus courts chemins
    for(auto& [key, val] : pathsTo){
        for(auto& [neighbor, distance] : val){
            shortestPath.push(neighbor);
        }
        int remote{1};
        while(shortestPath.size() > 0){
            unsigned long level{shortestPath.size()};
            remote++;
            while(level > 0){
                std::string temp{shortestPath.front()};
                shortestPath.pop();
                for(auto& [opposedKey, opposedVal] : pathsTo.at(temp)){
                    if(key != opposedKey && pathsTo.at(key).find(opposedKey) == pathsTo.at(key).end() && opposedVal == 1){
                        pathsTo.at(key).insert(std::make_pair(opposedKey, remote));
                        shortestPath.push(opposedKey);
                    }
                }
                level--;
            }
        }
    }
    std::vector<std::string> toBeDeleted;
    for(auto& [key, val] : pathsTo){
        if(pressure.find(key) == pressure.end() && key != "AA"){        // on doit garder AA car c'est le point de départ
            toBeDeleted.push_back(key);
        }
        std::vector<std::string> toBeTrashed;
        for(auto& [neighbor, distance] : val){
            if(pressure.find(neighbor) == pressure.end() && neighbor != "AA"){
                toBeTrashed.push_back(neighbor);
            }
        }
        for(auto& trashed : toBeTrashed){
            val.erase(trashed);
        }
    }
    for(auto& deleted : toBeDeleted){
        pathsTo.erase(deleted);
    }
    for(auto& [key, val] : pathsTo){
        binaryGraph.insert(std::make_pair(binaryEquivalent.at(key), std::unordered_map<int, int>{}));
        for(auto& [neighbor, distance] : val){
            binaryGraph.at(binaryEquivalent.at(key)).insert(std::make_pair(binaryEquivalent.at(neighbor), distance));
        }
    }
    int bothPartsRes{0};
    for(int i = 1; i <= 32768; i = i + 2){
        int a = i;                              // les valves qu'on ne peut pas ouvrir sont considérées comme ouvertes dès le départ
        int b = a ^ 65534;
        b |= 1;
        followPaths(1, 1, 0, binaryPressure, binaryGraph, a, 0, 0);
        int partA{res};
        res = 0;
        followPaths(1, 1, 0, binaryPressure, binaryGraph, b, 0, 0);
        int partB{res};
        res = 0;
        bothPartsRes = std::max(bothPartsRes, partA + partB);       // on effectue deux fois la recherche indépendamment l'une de l'autre
    }
    std::cout << bothPartsRes << "\n";
    return 0;
}