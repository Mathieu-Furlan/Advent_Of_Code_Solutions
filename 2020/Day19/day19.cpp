#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

std::string zeroVal(int rule, std::unordered_map<int, std::string>& equival, std::unordered_map<int, std::vector<std::string>>& rulesBinder){
    std::cout << rule << "\n";
    if(equival.find(rule) != equival.end()){
        return equival.at(rule);
    }
    std::string equivalent;
    int rulesCounter{0};
    for(auto& ruleLabels : rulesBinder.at(rule)){
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
            equivalent += zeroVal(std::stoi(ruleLabels.substr(0, separator)), equival, rulesBinder);
            equivalent += zeroVal(std::stoi(ruleLabels.substr(separator + 1)), equival, rulesBinder);
        }
        else equivalent += zeroVal(std::stoi(ruleLabels), equival, rulesBinder);
        rulesCounter++;
    }
    std::cout << "equivalent: " << equivalent << "\n";
    return equivalent;
}

int main(){
    std::ifstream file("inputtest");
    std::string s;
    std::unordered_map<int, std::string> equivalences;
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
            std::vector<std::string> rulesCollector;
            for(int i = index; i < s.length(); i++){
                if(s[i] == '"'){
                    std::string init{s[i + 1]};
                    equivalences.insert(std::make_pair(rule, init));
                    break;
                }
                else if(s[i] == '|'){
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
    for(auto& [key, val] : equivalences){
        std::cout << key << ": " << val << "\n";
    }
    std::string res{zeroVal(0, equivalences, rules)};
    std::cout << res << "\n";
    return 0;
}