#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <cmath>

int main(){
    std::cout << std::setprecision(10);
    std::unordered_map<std::string, float> inventory;
    inventory.insert(std::make_pair("ORE", 0));
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, int> quantityProduced;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> reactions;
    while(getline(file, s)){
        int quantity;
        std::string quant;
        std::string chemical;
        std::unordered_map<std::string, int> subComponents;
        for(int i = 0; i < s.length(); i++){
            if(s[i] >= 48 && s[i] <= 57){
                while(s[i] >= 48 && s[i] <= 57){
                    quant += s[i];
                    i++;
                }
                quantity = std::stoi(quant);
                quant.clear();
            }
            else if(s[i] >= 65 && s[i] <= 90){
                while(s[i] >= 65 && s[i] <= 90){
                    chemical += s[i];
                    i++;
                }
                subComponents.insert(std::make_pair(chemical, quantity));
                chemical.clear();
            }
            else if(s[i] == '>'){
                i++;
                std::string remainingQuant;
                std::string obtainedChemical;
                while(i < s.length()){
                    if(s[i] >= 48 && s[i] <= 57){
                        remainingQuant += s[i];
                    }
                    else if(s[i] >= 65 && s[i] <= 90){
                        obtainedChemical += s[i];
                    }
                    i++;
                }
                reactions.insert(std::make_pair(obtainedChemical, subComponents));
                quantityProduced.insert(std::make_pair(obtainedChemical, std::stoi(remainingQuant)));
                inventory.insert(std::make_pair(obtainedChemical, 0));
            }
        }
    }
    std::vector<std::string> topologicalOrder;
    std::queue<std::string> noIncomingEdges;
    noIncomingEdges.push("ORE");
    std::unordered_set<std::string> alreadySorted{"ORE"};
    while(noIncomingEdges.size() > 0){
        std::string tempChem{noIncomingEdges.front()};
        noIncomingEdges.pop();
        topologicalOrder.push_back(tempChem);
        for(auto& [key, val] : reactions){
            if(alreadySorted.find(key) == alreadySorted.end()){
                bool addToList{true};
                for(auto& [comp, quant] : val){
                    if(alreadySorted.find(comp) == alreadySorted.end()){
                        addToList = false;
                        break;
                    }
                }
                if(addToList){
                    noIncomingEdges.push(key);
                    alreadySorted.insert(key);
                }
            }
        }
    }
    for(int i = 0; i < topologicalOrder.size(); i++){
        std::cout << topologicalOrder[i] << "\n";
    }
    inventory.at("FUEL")++;     // on considère qu'on a déjà le résultat et on calcule en sens inverse
    for(int i = topologicalOrder.size() - 1; i > 0; i--){
        for(auto& [key, val] : reactions.at(topologicalOrder[i])){      // les réactions se font dans l'ordre topologique inversé, on sait à l'avance de quelle quantité on a besoin
            inventory.at(key) += val * std::ceil(inventory.at(topologicalOrder[i]) / quantityProduced.at(topologicalOrder[i]));
        }
    }
    for(auto& [key, val] : inventory){
        std::cout << key << " : " << val << "\n";
    }
    std::cout << inventory.at(topologicalOrder[0]) << "\n";
    return 0;
}