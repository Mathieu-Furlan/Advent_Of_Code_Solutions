#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int res{0};

void findArrangements(std::string stateSprings, int index, std::vector<int>& aggregate, int maxDamaged, int currentlyDamaged){
    if(index == stateSprings.length()){
        bool meetRequirements{true};
        int succesive{0};
        int ind{0};
        for(auto& character : stateSprings){
            if(character == '#'){
                succesive++;
            }
            else if(succesive > 0){
                if(succesive == aggregate[ind]){
                    ind++;
                    succesive = 0;
                }
                else{
                    meetRequirements = false;
                    break;
                }
            }
        }
        if(succesive > 0){                      // si il reste un élément à comparer
            if(succesive != aggregate[ind]){
                meetRequirements = false;
            }
            ind++;
        }
        if(ind < aggregate.size()){         // si il y a le nombre suffisant d'élément
            meetRequirements = false;
        }
        if(meetRequirements){
            res++;
        }
        return;
    }
    if(stateSprings[index] == '?'){
        if(currentlyDamaged < maxDamaged){              // on teste d'abord avec "#" si c'est possible
            stateSprings[index] = '#';
            findArrangements(stateSprings, index + 1, aggregate, maxDamaged, currentlyDamaged + 1);
        }
        stateSprings[index] = '.';                      // on essaie ensuite avec "."
        findArrangements(stateSprings, index + 1, aggregate, maxDamaged, currentlyDamaged);
    }
    else if(stateSprings[index] == '#'){
        if(currentlyDamaged < maxDamaged){              // si on peut encore ajouter un "#"
            findArrangements(stateSprings, index + 1, aggregate, maxDamaged, currentlyDamaged + 1);
        }
    }
    else findArrangements(stateSprings, index + 1, aggregate, maxDamaged, currentlyDamaged);  // si c'est un "."
}

int main(){
    std::ifstream file("input");
    std::string s;
    while(getline(file, s)){
        std::string springs{s.substr(0, s.find(' '))};
        std::string value;
        std::vector<int> contiguous;
        int unknownDamaged{0};                  // le nombre maximum de "#" est égal à la somme des éléments du vecteur 
        for(int i = s.find(' ') + 1; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58){
                value += s[i];
            }
            else{
                contiguous.push_back(std::stoi(value));
                unknownDamaged += std::stoi(value);
                value.clear();
            }
        }
        contiguous.push_back(std::stoi(value));
        unknownDamaged += std::stoi(value);
        std::cout << springs << " ";
        for(auto& elem : contiguous){
            std::cout << elem << " ";
        }
        std::cout << "\n";
        findArrangements(springs, 0, contiguous, unknownDamaged, 0);
        std::cout << "res " << res << "\n";
    }
    std::cout << res << "\n";
    return 0;
}