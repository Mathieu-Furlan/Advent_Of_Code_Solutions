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
            value += s[6];
            if(s.length() >= 8){
                value += s[7];
                if(s.length() == 9){       // il y a un nombre à trois chiffres
                    value += s[8];
                }
            }
            immediateMonkeys.insert(std::make_pair(s.substr(0, 4), std::stoi(value)));
        }
        else{
            remoteMonkeys.insert(std::make_pair(s.substr(0, 4), std::array<std::string, 3>{{s.substr(6, 4), s.substr(13, 4), s.substr(11, 1)}}));
        }
    }
    bool found{false};
    while(!found){
        std::vector<std::string> toBeDeleted;
        for(auto& [key, val] : remoteMonkeys){
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
                if(key == "root"){
                    found = true;
                }
                toBeDeleted.push_back(key);
            }
        }
        for(auto& deleted: toBeDeleted){
            remoteMonkeys.erase(deleted);
        }
    }
    std::cout << immediateMonkeys.at("root") << "\n";
    return 0;
}