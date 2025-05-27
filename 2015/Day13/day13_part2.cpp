#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <array>

int res{0};
const int GUESTS{9};

void permutations(std::array<char, GUESTS>& seating, int index, std::unordered_map<char, std::unordered_map<char, int>>& relation){
    if(index == GUESTS - 1){
        int satisfaction{0};
        for(int i = 0; i <= seating.size() - 1; i++){
            if(i == 0){
                satisfaction += relation.at(seating[i]).at(seating[GUESTS - 1]);
                satisfaction += relation.at(seating[i]).at(seating[i + 1]);
            }
            else if(i == GUESTS - 1){
                satisfaction += relation.at(seating[i]).at(seating[i - 1]);
                satisfaction += relation.at(seating[i]).at(seating[0]);
            }
            else{
                satisfaction += relation.at(seating[i]).at(seating[i - 1]);
                satisfaction += relation.at(seating[i]).at(seating[i + 1]);
            }
        }
        if(satisfaction > res){
            res = satisfaction;
        }
    }
    else if(index > GUESTS - 1){
        return;
    }
    for(int i = index; i <= GUESTS - 1; i++){
        if(i != index){
            std::swap(seating[i], seating[index]);
            permutations(seating, index + 1, relation);
            std::swap(seating[index], seating[i]);
        }
        else permutations(seating, index + 1, relation);
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<char, std::unordered_map<char, int>> happiness;
    while(getline(file, s)){
        int spaceCount{0};
        char personA{'?'};
        char personB{'?'};
        std::string value;
        bool negativeValue{false};
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 64 && s[i] < 91){
                if(personA == '?'){
                    personA = s[i];
                }
                else personB = s[i];
            }
            else if(s[i] == ' '){
                spaceCount++;
                if(spaceCount == 2){
                    if(s[i + 1] == 'l'){
                        negativeValue = true;
                    }
                }
            }
            else if(s[i] > 47 && s[i] < 58){
                value += s[i];
            }
        }
        if(negativeValue){
            value = '-' + value;
        }
  
        if(happiness.find(personA) != happiness.end()){
            happiness.at(personA).insert(std::make_pair(personB, std::stoi(value)));
        }
        else{
            std::unordered_map<char, int> initMap;
            initMap.insert(std::make_pair(personB, std::stoi(value)));
            happiness.insert(std::make_pair(personA, initMap));
        }
    }
    std::unordered_map<char, int> lastGuest;
    happiness.insert(std::make_pair('X', lastGuest));
    for(auto& [key, val] : happiness){
        if(key != 'X'){                             // on insère le dernier invité pour chaque personne
            val.insert(std::make_pair('X', 0));
        }
        happiness.at('X').insert(std::make_pair(key, 0));   // on insère chaque invité pour le dernier arrivé
    }
    std::array<char, GUESTS> seatingArangement{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'M', 'X'};
    permutations(seatingArangement, 0, happiness);
    std::cout << res << "\n";
    return 0;
}