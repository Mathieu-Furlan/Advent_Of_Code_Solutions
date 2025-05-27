#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

// greedy ne donne pas toujours le bon résultat et ne peut pas être utilisé

// la fonction récursive pourrait être plus rapide avec memoization
long evaluateComposition(int itemsQuantity, int cumulatedWeight, int index, int requiredNumberItems, std::vector<int>& packages, int targetWeight, long entanglement){
    if(cumulatedWeight == targetWeight && itemsQuantity == requiredNumberItems){
        return entanglement;
    }
    if(index >= packages.size()){
        return std::numeric_limits<long>::max();        // si on n'a pas choisi assez d'éléments
    }
    return std::min(evaluateComposition(itemsQuantity + 1, cumulatedWeight + packages[index], index + 1, requiredNumberItems, packages, targetWeight, entanglement == 0 ? packages[index] : entanglement * packages[index]), evaluateComposition(itemsQuantity, cumulatedWeight, index + 1, requiredNumberItems, packages, targetWeight, entanglement));
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<int> weights;
    int totalWeight{0};
    while(getline(file, s)){
        totalWeight += std::stoi(s);
        weights.push_back(std::stoi(s));
    }
    int firstCompartment{totalWeight / 3};
    std::sort(weights.begin(), weights.end(), [](int a, int b){
        return a > b;
    });
    std::vector<int> passengerCompartment;
    int passengerWeight{0};
    int packageQuantity{0};
    for(int i = 0; i <= weights.size() - 1; i++){
        if(passengerWeight + weights[i] <= firstCompartment){
            passengerWeight += weights[i];
            packageQuantity++;
        }
    }
    long res{evaluateComposition(0, 0, 0, packageQuantity, weights, firstCompartment, 0)};
    std::cout << res << "\n";
    return 0;
}