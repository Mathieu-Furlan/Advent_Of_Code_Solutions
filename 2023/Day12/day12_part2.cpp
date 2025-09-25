#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

long findArrangements(std::string& stateSprings, int index, std::vector<int>& aggregate, int indexAggreg, int maxDamaged, int currentlyDamaged, int aggregateDamaged, int previousDamaged, std::vector<std::vector<std::vector<long>>>& memory){
    if(memory[index][currentlyDamaged][previousDamaged] > -1){
        return memory[index][currentlyDamaged][previousDamaged];
    }
    if(indexAggreg < aggregate.size() && aggregateDamaged == aggregate[indexAggreg]){
        indexAggreg++;
        aggregateDamaged = 0;
    }
    if(index == stateSprings.length()){
        if(indexAggreg == aggregate.size()){
            return 1;
        }
        else return 0;
    }
    long res{0};
    if(stateSprings[index] == '?'){
        if(currentlyDamaged < maxDamaged && indexAggreg < aggregate.size() && !(aggregateDamaged == 0 && previousDamaged)){              // on teste d'abord avec "#" si c'est possible
            res += findArrangements(stateSprings, index + 1, aggregate, indexAggreg, maxDamaged, currentlyDamaged + 1, aggregateDamaged + 1, 1, memory);
        }
        if(aggregateDamaged == 0){                  // on essaie ensuite avec "."
            res += findArrangements(stateSprings, index + 1, aggregate, indexAggreg, maxDamaged, currentlyDamaged, aggregateDamaged, 0, memory);
        }
    }
    else if(stateSprings[index] == '#'){
        if(currentlyDamaged < maxDamaged && indexAggreg < aggregate.size() && !(aggregateDamaged == 0 && previousDamaged)){              // si on peut encore ajouter un "#"
            res += findArrangements(stateSprings, index + 1, aggregate, indexAggreg, maxDamaged, currentlyDamaged + 1, aggregateDamaged + 1, 1, memory);
        }
    }
    else if(aggregateDamaged == 0){
        res += findArrangements(stateSprings, index + 1, aggregate, indexAggreg, maxDamaged, currentlyDamaged, aggregateDamaged, 0, memory);  // si c'est un "."
    }
    memory[index][currentlyDamaged][previousDamaged] = res;
    return res;
}

int main(){
    std::ifstream file("input");
    std::string s;
    long final{0};
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
        unsigned long contiguousSize{contiguous.size()};
        std::string springCopy{springs};
        for(int i = 1; i < 5; i++){
            springs += '?' + springCopy;
            for(int j = 0; j < contiguousSize; j++){
                contiguous.push_back(contiguous[j]);
            }
        }
        unknownDamaged += std::stoi(value);
        unknownDamaged *= 5;
        std::cout << springs << " ";
        for(auto& elem : contiguous){
            std::cout << elem << " ";
        }
        std::cout << "\n";
        std::vector<std::vector<std::vector<long>>> mem;
        for(int i = 0; i <= springs.length(); i++){
            std::vector<std::vector<long>> matrixCells;
            for(int j = 0; j <= unknownDamaged; j++){
                std::vector<long> init{-1, -1};
                matrixCells.push_back(init);
            }
            mem.push_back(matrixCells);
        }
        final += findArrangements(springs, 0, contiguous, 0, unknownDamaged, 0, 0, 0, mem);
        std::cout << "res " << final << "\n";
    }
    std::cout << "res " << final << "\n";
    return 0;
}