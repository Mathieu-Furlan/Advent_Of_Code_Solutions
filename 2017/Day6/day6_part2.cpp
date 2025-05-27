#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>

int main(){
    std::ifstream infile("input");
    std::string s;
    int res = 0;
    std::vector<int> memBanks;
    std::string stringRepresentation;
    bool cycle{false};
    bool repeat{false};
    std::string stateToFind;
    while(infile >> s){
        memBanks.push_back(stoi(s));
        stringRepresentation += s;
    }
    unsigned long memBanksSize{memBanks.size()};
    std::unordered_set<std::string> stateMem;
    stateMem.insert(stringRepresentation);
    stringRepresentation.clear();
    while(!repeat){
        if(cycle){
            res++;
        }
        int maxVal{0};
        int indexMax{-1};
        for(int i = 0; i <= memBanksSize - 1; i++){
            if(memBanks[i] > maxVal){
                maxVal = memBanks[i];
                indexMax = i;
            }
        }
        memBanks[indexMax] = 0;
        indexMax = (indexMax + 1) % memBanksSize;            // dans le cas où l'indice est le dernier du vecteur
        double reallocatedValue{std::floor(maxVal / memBanksSize)};
        for(int j = indexMax;; j = (j + 1) % memBanksSize){
            memBanks[j] += reallocatedValue;
            if(j == (indexMax - 1) % memBanksSize){                 // lorsque tous les éléments ont été augmenté
                break;
            }
        }
        unsigned long lastIncrease{maxVal % memBanksSize};
        while(lastIncrease > 0){
            memBanks[indexMax]++;
            lastIncrease--;
            indexMax++;
            if(indexMax == memBanksSize){
                indexMax = 0;
            }
        }
        for(int m = 0; m <= memBanksSize - 1; m++){
            stringRepresentation += std::to_string(memBanks[m]);
        }
        if(!cycle && stateMem.find(stringRepresentation) != stateMem.end()){  // lorsqu'on a détecté un cycle
            cycle = true;
            stateToFind = stringRepresentation;
        }
        else if(stringRepresentation == stateToFind){            // si on retrouve l'état de départ du cycle
            repeat = true;
        }
        stateMem.insert(stringRepresentation);
        stringRepresentation.clear();
    }
    std::cout << res << "\n";
    return res;
}