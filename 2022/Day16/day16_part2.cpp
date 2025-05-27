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

void followPaths(int minutes, std::string currentValve, int cumulatedPressure, std::unordered_map<std::string, int>& pressureMap, std::unordered_map<std::string, std::unordered_map<std::string, int>>& mazeMap, std::vector<std::string>& opened, int pressureReleased, int timeMoving, int elephantMoving, std::string elephantValve){
    std::cout << "minutes " << minutes << " cumulatedPress " << cumulatedPressure << "\n";
    if(minutes == 27){
        if(cumulatedPressure > res){
            res = cumulatedPressure;
        }
        return;
    }
    cumulatedPressure += pressureReleased;
    bool humanMove{true};
    if(timeMoving > 0){
        if(timeMoving == 1){                                    // on ajoute la pression supplémentaire lorsqu'il reste une minute de déplacement pour pouvoir continuer à se déplacer immédiatement après l'ouverture
            pressureReleased += pressureMap.at(currentValve);
        }
        timeMoving--;
        humanMove = false;
    }
    bool elephantMove{true};
    if(elephantMoving > 0){
        if(elephantMoving == 1){                                    // on ajoute la pression supplémentaire lorsqu'il reste une minute de déplacement pour pouvoir continuer à se déplacer immédiatement après l'ouverture
            pressureReleased += pressureMap.at(elephantValve);
        }
        elephantMoving--;
        elephantMove = false;
    }
    std::string nextValveHuman{currentValve};
    int travelHuman{0};
    std::string nextValveElephant{elephantValve};
    int travelElephant{0};
    if(opened.size() < mazeMap.size()){
        if(humanMove){
            for(auto& [key, val] : mazeMap.at(currentValve)){
                if(std::find(opened.begin(), opened.end(), key) == opened.end()){
                    opened.push_back(key);
                    std::cout << "human " << key << "\n";
                    nextValveHuman = key;
                    travelHuman = val;
                    break;
                }
            }
        }
        if(elephantMove && opened.size() < mazeMap.size()){
            for(auto& [key, val] : mazeMap.at(elephantValve)){
                if(std::find(opened.begin(), opened.end(), key) == opened.end()){
                    opened.push_back(key);
                    std::cout << "eleph " << key << "\n";
                    nextValveElephant = key;
                    travelElephant = val;
                    break;
                }
            }
        }
        followPaths(minutes + 1, nextValveHuman, cumulatedPressure, pressureMap, mazeMap, opened, pressureReleased, travelHuman, travelElephant, nextValveElephant);
        if(humanMove){
            opened.pop_back();
        }
        if(elephantMove){
            opened.pop_back();
        }
    }
    else if(opened.size() == mazeMap.size()){                   // si on a ouvert toutes les valves
        followPaths(minutes + 1, currentValve, cumulatedPressure, pressureMap, mazeMap, opened, pressureReleased, 0, 0, elephantValve);
    }
}

int main(){
    std::ifstream file("inputtest");
    std::string s;
    std::unordered_map<std::string, int> pressure;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> pathsTo;
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
        }
    }
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
        std::cout << "key " << key << "\n";
        for(auto& [neighbor, distance] : val){
            std::cout << "neighbor " << neighbor << " distance " << distance << "\n";
        }
    }
    std::vector<std::string> init{"AA"};
    followPaths(0, "AA", 0, pressure, pathsTo, init, 0, 0, 0, "AA");
    std::cout << res << "\n";
    return 0;
}