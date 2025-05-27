#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, std::vector<std::string>> replacements;
    std::string medicine;
    bool molecule{false};
    while(getline(file, s)){
        if(s.length() == 0){
            molecule = true;
            continue;
        }
        if(molecule){
            medicine = s;
        }
        std::string temp{s[0]};
        if(s[1] != ' '){
            temp += s[1];
        }
        for(int i = 2; i < s.length(); i++){
            if(s[i] == '='){
                if(replacements.find(temp) == replacements.end()){
                    std::vector<std::string> init;
                    init.push_back(s.substr(i + 3));
                    replacements.insert(std::make_pair(temp, init));
                }
                else replacements.at(temp).push_back(s.substr(i + 3));
            }
        }
    }
    std::unordered_set<std::string> molecules;
    for(int i = 0; i <= medicine.length() - 1; i++){
        if(replacements.find(medicine.substr(i, 1)) != replacements.end()){
            for(auto& replace : replacements.at(medicine.substr(i, 1))){
                molecules.insert(medicine.substr(0, i) + replace + medicine.substr(i + 1));
            }
        }
        if(i < medicine.length() - 1 && replacements.find(medicine.substr(i, 2)) != replacements.end()){
            for(auto& replace : replacements.at(medicine.substr(i, 2))){
                molecules.insert(medicine.substr(0, i) + replace + medicine.substr(i + 2));
            }
        }
    }
    std::cout << molecules.size() << "\n";
    return 0;
}