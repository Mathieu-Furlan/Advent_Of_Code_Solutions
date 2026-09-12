#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::string> vault;
    int row{0};
    std::unordered_map<char, std::array<int, 2>> pointsOfInterrest;
    while(getline(file, s)){
        vault.push_back(s);
        for(int i = 0; i < s.length(); i++){
            if((s[i] >= 97 && s[i] <= 122) || s[i] == '@'){
                pointsOfInterrest.insert(std::make_pair(s[i], std::array<int, 2>{row, i}));
            }
        }
        row++;
    }
    std::unordered_map<char, std::vector<std::array<int, 2>>> adjacencyList;
    for(auto)
    return 0;
}