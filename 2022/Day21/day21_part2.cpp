#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <array>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, long> immediateMonkeys;
    std::unordered_map<std::string, std::array<std::string, 3>> remoteMonkeys;
    while(getline(file, s)){
        std::string value;
        if(s[6] > 47 && s[6] < 58){
            int index{6};
            while(s[index] > 47 && s[index] < 58){
                value += s[index];
                index++;
            } 
            if(s.substr(0, 4) != "humn"){           // on cherche la valeur de humn
                immediateMonkeys.insert(std::make_pair(s.substr(0, 4), std::stol(value)));
            }
        }
        else{
            remoteMonkeys.insert(std::make_pair(s.substr(0, 4), std::array<std::string, 3>{{s.substr(6, 4), s.substr(13, 4), s.substr(11, 1)}}));
        }
    }
    bool found{false};
    while(!found){
        std::vector<std::string> toBeDeleted;
        for(auto& [key, val] : remoteMonkeys){
            if(immediateMonkeys.find("sour") != immediateMonkeys.end()){
                std::cout << immediateMonkeys.at("sour") << "\n";
            }           // si on connaît les deux valeurs
            if(immediateMonkeys.find(val[0]) != immediateMonkeys.end() && immediateMonkeys.find(val[1]) != immediateMonkeys.end()){
                if(val[2] == "+"){
                    immediateMonkeys.insert(std::make_pair(key, immediateMonkeys.at(val[0]) + immediateMonkeys.at(val[1])));
                }
                else if(val[2] == "-"){
                    immediateMonkeys.insert(std::make_pair(key, immediateMonkeys.at(val[0]) - immediateMonkeys.at(val[1])));
                }
                else if(val[2] == "*"){
                    immediateMonkeys.insert(std::make_pair(key, immediateMonkeys.at(val[0]) * immediateMonkeys.at(val[1])));
                }
                else if(val[2] == "/"){
                    immediateMonkeys.insert(std::make_pair(key, immediateMonkeys.at(val[0]) / immediateMonkeys.at(val[1])));
                }
                toBeDeleted.push_back(key);
                if(val[1] == "humn"){
                    found = true;
                }
            }               // si on connaît le résultat et la première valeur
            else if(immediateMonkeys.find(key) != immediateMonkeys.end() && immediateMonkeys.find(val[0]) != immediateMonkeys.end()){
                std::cout << "key " << immediateMonkeys.at(key) << "\n";
                std::cout << "val[0] " << immediateMonkeys.at(val[0]) << "\n";
                if(val[2] == "+"){
                    immediateMonkeys.insert(std::make_pair(val[1], immediateMonkeys.at(key) - immediateMonkeys.at(val[0])));
                }
                else if(val[2] == "-"){
                    immediateMonkeys.insert(std::make_pair(val[1], immediateMonkeys.at(val[0]) - immediateMonkeys.at(key)));
                }
                else if(val[2] == "*"){
                    immediateMonkeys.insert(std::make_pair(val[1], immediateMonkeys.at(key) / immediateMonkeys.at(val[0])));
                }
                else if(val[2] == "/"){
                    immediateMonkeys.insert(std::make_pair(val[1], immediateMonkeys.at(val[0]) / immediateMonkeys.at(key)));
                }
                toBeDeleted.push_back(key);
                if(val[1] == "humn"){
                    found = true;
                }
            }               // si on connaît le résultat et la deuxième valeur
            else if(immediateMonkeys.find(key) != immediateMonkeys.end() && immediateMonkeys.find(val[1]) != immediateMonkeys.end()){
                std::cout << "key " << immediateMonkeys.at(key) << "\n";
                std::cout << "val[1] " << immediateMonkeys.at(val[1]) << "\n";
                if(val[2] == "+"){
                    immediateMonkeys.insert(std::make_pair(val[0], immediateMonkeys.at(key) - immediateMonkeys.at(val[1])));
                }
                else if(val[2] == "-"){
                    immediateMonkeys.insert(std::make_pair(val[0], immediateMonkeys.at(key) + immediateMonkeys.at(val[1])));
                }
                else if(val[2] == "*"){
                    immediateMonkeys.insert(std::make_pair(val[0], immediateMonkeys.at(key) / immediateMonkeys.at(val[1])));
                }
                else if(val[2] == "/"){
                    immediateMonkeys.insert(std::make_pair(val[0], immediateMonkeys.at(key) * immediateMonkeys.at(val[1])));
                }
                toBeDeleted.push_back(key);
                if(val[0] == "humn"){
                    found = true;
                }
            }
            else if(key == "root"){             // si on connaît une valeur l'autre lui est égale
                if(immediateMonkeys.find(val[0]) != immediateMonkeys.end()){
                    immediateMonkeys.insert(std::make_pair(val[1], immediateMonkeys.at(val[0])));
                    toBeDeleted.push_back(key);
                }
                else if(immediateMonkeys.find(val[1]) != immediateMonkeys.end()){
                    immediateMonkeys.insert(std::make_pair(val[0], immediateMonkeys.at(val[1])));
                    toBeDeleted.push_back(key);
                }
            }
        }
        for(auto& deleted: toBeDeleted){
            remoteMonkeys.erase(deleted);
        }
    }
    std::cout << immediateMonkeys.at("humn") << "\n";
    return 0;
}