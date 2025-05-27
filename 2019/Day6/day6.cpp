#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, std::vector<std::string>> orbits;
    while(getline(file, s)){
        std::string center{s.substr(0, 3)};
        std::string planet{s.substr(4, 3)};
        if(orbits.find(center) == orbits.end()){
            std::vector<std::string> temp{planet};
            orbits.insert(std::make_pair(center, temp));
        }
        else orbits.at(center).push_back(planet);
    }
    int orbit{0};
    int res{0};
    std::vector<std::string> universe;
    universe.push_back("COM");
    while(universe.size() > 0){
        std::vector<std::string> next;
        for(auto& world : universe){
            if(orbits.find(world) != orbits.end()){
                for(auto& planets : orbits.at(world)){
                    next.push_back(planets);
                }
            }
        }
        universe.clear();
        universe = next;
        orbit++;
        res += orbit * universe.size();
    }
    std::cout << res << "\n";
    return res;
}