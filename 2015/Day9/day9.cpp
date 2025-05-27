#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <array>
#include <vector>
#include <limits>
#include <unordered_set>

//brute force où l'on teste toutes les combinaisons

int res{std::numeric_limits<int>::max()};   

// la hashMap en argument est passée par référence
void routesValues(std::unordered_map<std::string, std::vector<std::array<std::string, 2>>>& dest, std::string from, int cumulTravel, int visited, std::unordered_set<std::string> prevCities){
    if(visited == dest.size()){                             // si on a exploré toutes les villes
        if(cumulTravel < res){
            res = cumulTravel;
        }
        return;
    }
    std::cout << "from " << from << "\n";
    for(auto& elems : dest.at(from)){
        if(prevCities.find(elems[0]) == prevCities.end()){         // un hashSet qui contient les villes déjà visitées
            prevCities.insert(elems[0]);
            routesValues(dest, elems[0], cumulTravel + std::stoi(elems[1]), visited + 1, prevCities);
            prevCities.erase(elems[0]);
        }
    }
    return;
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, std::vector<std::array<std::string, 2>>> pathes;
    while(getline(file, s)){
        std::string cityFrom;
        std::string cityTo;
        std::string distance;
        for(int i = 0; i <= s.length() - 1; i++){
            if(i == 0 && s[i] > 64 && s[i] < 91){
                int index{i};
                while(s[index] > 32){
                    cityFrom += s[index];
                    index++;
                    i++;
                }
            }
            else if(s[i] > 64 && s[i] < 91){
                int index{i};
                while(s[index] > 32){
                    cityTo += s[index];
                    index++;
                    i++;
                }
            }
            else if(s[i] > 47 && s[i] < 58){
                int index{i};
                while(index < s.length() && s[index] > 32){
                    distance += s[index];
                    index++;
                    i++;
                }
            }
        }
        if(pathes.find(cityFrom) != pathes.end()){
            pathes.at(cityFrom).push_back({cityTo, distance});
        }
        else pathes.insert(std::make_pair(cityFrom, std::vector{std::array{cityTo, distance}}));
        if(pathes.find(cityTo) != pathes.end()){                                                    // le graphique est de type undirected, les distances sont valables dans les deux sens
            pathes.at(cityTo).push_back({cityFrom, distance});
        }
        else pathes.insert(std::make_pair(cityTo, std::vector{std::array{cityFrom, distance}}));
    }
    for(auto& pair : pathes){
        routesValues(pathes, pair.first, 0, 1, std::unordered_set<std::string>{pair.first});
    }
    std::cout << res << "\n";
    return res;
}