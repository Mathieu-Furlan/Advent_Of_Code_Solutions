#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int recursiveRes{0};

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
            recursiveRes++;
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
    std::ifstream file("inputtest");
    std::string s;
    long res{0};
    while(getline(file, s)){
        bool useSpring{false};
        std::string springs{s.substr(0, s.find(' '))};
        std::string additionalSprings{springs[springs.length() - 1] == '#' ? springs : '?' + springs};
        if(springs[springs.length() - 1] == '?'){
            int deleteCount{0};
            for(int i = 0; i <= additionalSprings.length() - 1; i++){
                if(additionalSprings[i] == '?'){
                    springs += additionalSprings[i];
                    deleteCount++;
                }
                else break;
            }
            additionalSprings = additionalSprings.substr(deleteCount);
            useSpring = true;
        }
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
        std::cout << additionalSprings << " ";
        for(auto& elem : contiguous){
            std::cout << elem << " ";
        }
        std::cout << "\n";
        findArrangements(springs, 0, contiguous, unknownDamaged, 0);
        int firstPart{recursiveRes};
        recursiveRes = 0;
        findArrangements(additionalSprings, 0, contiguous, unknownDamaged, 0);
        int secondPart{recursiveRes};
        recursiveRes = 0;
        std::cout << "firstPart " << firstPart << "\n";
        std::cout << "secondPart " << secondPart << "\n";
        if(useSpring){
            res += secondPart * firstPart * firstPart * firstPart * firstPart;
        }
        else res += secondPart * secondPart * secondPart * secondPart * firstPart;
        std::cout << res << "\n";
    }
    std::cout << res << "\n";
    return 0;
}