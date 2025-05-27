#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::unordered_map<std::string, std::string> workFlows;
    std::unordered_map<char, int> partRatings;
    while(getline(file, s)){
        if(s[0] > 96 && s[0] < 123){                        // crée une hashmap contenant la première partie du fichier txt
            std::string key;
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] == 123){
                    std::string value{s.substr(i + 1)};
                    value.pop_back();
                    workFlows.insert(std::make_pair(key, value));
                    break;
                }
                else{
                    key += s[i];
                }
            }
        }
        else if(s[0] == '{'){                       // si la ligne est une instruction
            int index{0};
            for(int i = 0; i <= s.length() - 1; i++){               // on ajoute les éléments de la ligne dans une hashmap
                if(s[i] == 'x' || s[i] == 'm' || s[i] == 'a' || s[i] == 's'){
                    std::string value;
                    index = i + 2;
                    while(s[index] > 47 && s[index] < 58){
                        value += s[index];
                        index++;
                    }
                    partRatings.insert(std::make_pair(s[i], stoi(value)));
                }
            }
            std::string currInstruct{"in"};
            bool continueProcess{true};
            std::cout << "new part ratings " << "\n";
            while(continueProcess){
                std::cout << "currInstruct " << currInstruct << "\n";
                std::string instructions{workFlows.at(currInstruct)};
                int ind{0};
                while(ind <= instructions.length() - 1){
                    long unsigned delimeter{instructions.find(',', ind)};
                    if(delimeter <= instructions.length() - 1){            // si il reste une comparaison à effectuer
                        std::string comparator;
                        std::string result;
                        for(int j = ind; j <= delimeter; j++){
                            if(instructions[j] > 47 && instructions[j] < 58){
                                comparator += instructions[j];
                            }
                            else if(instructions[j] == ':'){
                                result = instructions.substr(j + 1, delimeter - 1 - j);
                                break;
                            }
                        }
                        if(instructions[ind + 1] == '>'){
                            if(partRatings.at(instructions[ind]) > stoi(comparator)){
                                if(result.length() > 1){
                                    currInstruct = result;
                                    break;
                                }
                                else if(result[0] == 'A'){
                                    for(auto& [key, value] : partRatings){
                                        res += value;
                                    }
                                    continueProcess = false;
                                    break;
                                }
                                else if(result[0] == 'R'){
                                    continueProcess = false;
                                    break;
                                }
                            }
                        }
                        else if(instructions[ind + 1] == '<'){
                            if(partRatings.at(instructions[ind]) < stoi(comparator)){
                                if(result.length() > 1){
                                    currInstruct = result;
                                    break;
                                }
                                else if(result[0] == 'A'){
                                    for(auto& [key, value] : partRatings){
                                        res += value;
                                    }
                                    continueProcess = false;
                                    break;
                                }
                                else if(result[0] == 'R'){
                                    continueProcess = false;
                                    break;
                                }
                            }
                        }
                        ind = delimeter + 1;
                    }
                    else{                     // si on arrive à la fin de la ligne, toutes les comparaisons sont fausses
                        std::string result{instructions.substr(ind)};
                        if(result.length() > 1){
                            currInstruct = result;
                            break;
                        }
                        else if(result[0] == 'A'){
                            for(auto& [key, value] : partRatings){
                                res += value;
                            }
                            continueProcess = false;
                            break;
                        }
                        else if(result[0] == 'R'){
                            continueProcess = false;
                            break;
                        }
                    }
                }
            }
            partRatings.clear();
        }
    }
    std::cout << res << "\n";
    return res;
}