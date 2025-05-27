#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>
#include <limits>
#include <algorithm>

int res{std::numeric_limits<int>::max()};           // le code donne la bonne réponse mais s'exécute sans fin

void reduceString(std::string start, std::vector<std::array<std::string, 2>>& reduced, int steps, std::unordered_set<std::string>& mem){
    std::cout << start << "\n";
    if(start == "e"){
        if(steps < res){
            res = steps;
        }
        return;
    }
    if(mem.find(start) != mem.end() || steps >= res){
        return;
    }
    for(auto& elems : reduced){
        std::string::size_type index = start.find(elems[0]);
        if(index != std::string::npos){
            reduceString(start.substr(0, index) + elems[1] + start.substr(index + elems[0].length()), reduced, steps + 1, mem);
        }
    }
    mem.insert(start);
    return;
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<std::string, 2>> replacements;
    std::string medicine;
    bool molecule{false};
    while(getline(file, s)){
        if(s.length() == 0){
            molecule = true;
            continue;
        }
        if(molecule){
            medicine = s;
        }
        std::string temp{s[0]};
        if(s[1] != ' '){
            temp += s[1];
        }
        for(int i = 2; i < s.length(); i++){
            if(s[i] == '='){
                std::array<std::string, 2> molecule{{s.substr(i + 3), temp}};
                replacements.push_back(molecule);
            }
        }
    }
    std::sort(replacements.begin(), replacements.end(), [](const std::array<std::string, 2>& a, const std::array<std::string, 2>& b){
        if(a[0].length() > b[0].length()){
            return true;
        }
        else return false;
    });
    std::unordered_set<std::string> init;
    reduceString(medicine, replacements, 0, init);
    std::cout << res << "\n";
    return 0;
}