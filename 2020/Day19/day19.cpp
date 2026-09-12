#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cctype>

std::string zeroVal(int rule, std::unordered_map<int, std::vector<std::string>>& rulesBinder){
    std::cout << rule << "\n";
    std::vector<std::string> rulesSet{rulesBinder.at(rule)};
    if(rulesSet.size() == 1 && std::isalpha(rulesSet[0][0])){            // si une règle correspond directement à une lettre
        return rulesSet[0];
    }
    std::string equivalent;
    int rulesCounter{0};
    for(auto& ruleLabels : rulesSet){
        if(rulesCounter){
            equivalent += ' ';
        }
        int separator{0};
        for(int i = 0; i < ruleLabels.length(); i++){
            if(ruleLabels[i] == ' '){
                separator = i;
                break;
            }
        }
        if(separator){
            equivalent += zeroVal(std::stoi(ruleLabels.substr(0, separator)), rulesBinder);
            equivalent += zeroVal(std::stoi(ruleLabels.substr(separator + 1)), rulesBinder);
        }
        else equivalent += zeroVal(std::stoi(ruleLabels), rulesBinder);
        rulesCounter++;
    }
    std::cout << "equivalent: " << equivalent << "\n";
    return equivalent;
}

int main(){
    std::ifstream file("inputtest");
    std::string s;
    std::unordered_map<int, std::vector<std::string>> rules;
    std::vector<std::string> candidates;
    while(getline(file, s)){
        if(s[0] > 47 && s[0] < 58){                             // la première partie du fichier texte
            std::string ruleNumb;
            int index{0};
            while(s[index] > 47 && s[index] < 58){
                ruleNumb += s[index];
                index++;
            }
            index += 2;
            int rule{std::stoi(ruleNumb)};
            for(int i = index; i < s.length(); i++){
                if(s[i] == '"'){
                    std::string init{s[i + 1]};
                    rules.insert(std::make_pair(rule, std::vector<std::string>{init}));
                    break;
                }
                std::vector<std::string> rulesCollector;
                if(s[i] == '|'){
                    rulesCollector.push_back(s.substr(index, i - index - 1));
                    index = i + 2;
                }
                else if(i == s.length() - 1){
                    rulesCollector.push_back(s.substr(index));
                    rules.insert(std::make_pair(rule, rulesCollector));
                }
            }
        }
        else candidates.push_back(s);                                  // la deuxième partie du fichier texte
    }
    for(auto& [key, val] : rules){
        std::cout << key << ": ";
        for(auto& rule : val){
            std::cout << rule << ", ";
        }
        std::cout << "\n";
    }
    std::string res{zeroVal(0, rules)};
    std::cout << res << "\n";
    return 0;
}