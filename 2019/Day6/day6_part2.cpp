#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, std::vector<std::string>> orbits;
    std::unordered_map<std::string, std::vector<std::string>> reverseOrbits;
    std::string start;
    std::string destination;
    while(getline(file, s)){
        std::string center{s.substr(0, 3)};
        std::string planet{s.substr(4, 3)};
        if(planet == "YOU"){
            start = center;
        }
        else if(planet == "SAN"){
            destination = center;
        }
        if(orbits.find(center) == orbits.end()){
            std::vector<std::string> temp{planet};
            orbits.insert(std::make_pair(center, temp));
        }
        else orbits.at(center).push_back(planet);
        if(reverseOrbits.find(planet) == reverseOrbits.end()){
            std::vector<std::string> temp{center};
            reverseOrbits.insert(std::make_pair(planet, temp));
        }
        else reverseOrbits.at(planet).push_back(center);
    }
    int orbit{0};
    std::unordered_set<std::string> visited;
    visited.insert("YOU");
    std::vector<std::string> universe;
    universe.push_back(start);
    visited.insert(start);
    while(universe.size() > 0){
        std::vector<std::string> next;
        for(auto& world : universe){
            std::cout << world << "\n";
            if(world == destination){
                std::cout << orbit << "\n";
                return orbit;
            }
            if(orbits.find(world) != orbits.end()){
                for(auto& planets : orbits.at(world)){
                    if(visited.find(planets) == visited.end()){
                        next.push_back(planets);
                        visited.insert(planets);
                    }
                }
            }
            if(reverseOrbits.find(world) != orbits.end()){
                for(auto& planets : reverseOrbits.at(world)){
                    if(visited.find(planets) == visited.end()){
                        next.push_back(planets);
                        visited.insert(planets);
                    }
                }
            }
        }
        universe.clear();
        universe = next;
        orbit++;
    }
    std::cout << orbit << "\n";
    return orbit;
}