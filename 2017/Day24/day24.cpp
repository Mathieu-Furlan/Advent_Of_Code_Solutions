#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>

int res{0};

void bridgeBuilder(int port, std::unordered_set<int>& used, int strength, std::vector<std::array<int, 2>>& components){
    if(strength > res){
        res = strength;
    }
    for(int i = 0; i <= components.size() - 1; i++){
        if(used.find(i) == used.end() && components[i][0] == port){
            used.insert(i);
            bridgeBuilder(components[i][1], used, strength + components[i][0] + components[i][1], components);
            used.erase(i);
        }
        else if(used.find(i) == used.end() && components[i][1] == port){
            used.insert(i);
            bridgeBuilder(components[i][0], used, strength + components[i][1] + components[i][0], components);
            used.erase(i);
        }
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<int, 2>> components;
    while(getline(file, s)){
        bool slash{false};
        std::string port1;
        std::string port2;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58 && !slash){
                port1 += s[i];
            }
            else if(s[i] == '/'){
                slash = true;
            }
            else if(s[i] > 47 && s[i] < 58 && slash){
                port2 += s[i];
            }
        }
        components.push_back({std::stoi(port1), std::stoi(port2)});
    }
    for(int j = 0; j <= components.size() - 1; j++){
        if(components[j][0] == 0){
            std::unordered_set<int> init;
            init.insert(j);
            bridgeBuilder(components[j][1], init, components[j][1], components);
        }
        else if(components[j][1] == 0){
            std::unordered_set<int> init;
            init.insert(j);
            bridgeBuilder(components[j][0], init, components[j][0], components);
        }
    }
    std::cout << res << "\n";
    return res;
}