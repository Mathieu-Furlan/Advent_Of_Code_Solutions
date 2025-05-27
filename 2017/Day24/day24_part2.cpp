#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>

int res{0};
int longestBridge{0};

void highestLength(int port, std::unordered_set<int>& used, int length, std::vector<std::array<int, 2>>& components){
    if(length > longestBridge){
        longestBridge = length;
    }
    for(int i = 0; i <= components.size() - 1; i++){
        if(used.find(i) == used.end() && components[i][0] == port){
            used.insert(i);
            highestLength(components[i][1], used, length + 1, components);
            used.erase(i);
        }
        else if(used.find(i) == used.end() && components[i][1] == port){
            used.insert(i);
            highestLength(components[i][0], used, length + 1, components);
            used.erase(i);
        }
    }
}

void strongestBridge(int port, std::unordered_set<int>& used, int strength, int length, std::vector<std::array<int, 2>>& components){
    if(length == longestBridge){
        if(strength > res){
            res = strength;
        }
        return;
    }
    for(int i = 0; i <= components.size() - 1; i++){
        if(used.find(i) == used.end() && components[i][0] == port){
            used.insert(i);
            strongestBridge(components[i][1], used, strength + components[i][0] + components[i][1], length + 1, components);
            used.erase(i);
        }
        else if(used.find(i) == used.end() && components[i][1] == port){
            used.insert(i);
            strongestBridge(components[i][0], used, strength + components[i][1] + components[i][0], length + 1, components);
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
    for(int j = 0; j <= components.size() - 1; j++){            // on cherche la taille maximale
        if(components[j][0] == 0){
            std::unordered_set<int> init;
            init.insert(j);
            highestLength(components[j][1], init, 1, components);
        }
        else if(components[j][1] == 0){
            std::unordered_set<int> init;
            init.insert(j);
            highestLength(components[j][0], init, 1, components);
        }
    }
    for(int j = 0; j <= components.size() - 1; j++){           // on cherche le plus grand résultat avec la taille maximale
        if(components[j][0] == 0){
            std::unordered_set<int> init;
            init.insert(j);
            strongestBridge(components[j][1], init, components[j][1], 1, components);
        }
        else if(components[j][1] == 0){
            std::unordered_set<int> init;
            init.insert(j);
            strongestBridge(components[j][0], init, components[j][0], 1, components);
        }
    }
    std::cout << res << "\n";
    return res;
}