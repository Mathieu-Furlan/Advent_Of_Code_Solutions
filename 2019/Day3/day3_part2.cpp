#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::unordered_map<int, std::unordered_map<int, int>> firstWire;
    std::unordered_map<int, int> init;
    init.insert(std::make_pair(0, 0));
    firstWire.insert(std::make_pair(0, init));
    bool secondWire{false};
    while(getline(file, s)){
        if(!secondWire){
            int steps{0};
            int colWire{0};
            int rowWire{0};
            std::string value;
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] == 'R'){
                    int index{i + 1};
                    while(s[index] > 47 && s[index] < 58){
                        value += s[index];
                        index++;
                    }
                    int stopLoop{std::stoi(value)};
                    for(int j = 1; j <= stopLoop; j++){
                        steps++;
                        if(firstWire.find(colWire + j) == firstWire.end()){
                            std::unordered_map<int, int> tempMap;
                            tempMap.insert(std::make_pair(rowWire, steps));
                            firstWire.insert(std::make_pair(colWire + j, tempMap));
                        }
                        else if(firstWire.at(colWire + j).find(rowWire) == firstWire.at(colWire + j).end()){
                            firstWire.at(colWire + j).insert(std::make_pair(rowWire, steps));
                        }
                    }
                    colWire += stopLoop;
                    value.clear();
                    i++;
                }
                else if(s[i] == 'L'){
                    int index{i + 1};
                    while(s[index] > 47 && s[index] < 58){
                        value += s[index];
                        index++;
                    }
                    int stopLoop{std::stoi(value)};
                    for(int j = 1; j <= stopLoop; j++){
                        steps++;
                        if(firstWire.find(colWire - j) == firstWire.end()){
                            std::unordered_map<int, int> tempMap;
                            tempMap.insert(std::make_pair(rowWire, steps));
                            firstWire.insert(std::make_pair(colWire - j, tempMap));
                        }
                        else if(firstWire.at(colWire - j).find(rowWire) == firstWire.at(colWire - j).end()){
                            firstWire.at(colWire - j).insert(std::make_pair(rowWire, steps));
                        }
                    }
                    colWire -= stopLoop;
                    value.clear();
                    i++;
                }
                else if(s[i] == 'U'){
                    int index{i + 1};
                    while(s[index] > 47 && s[index] < 58){
                        value += s[index];
                        index++;
                    }
                    int stopLoop{std::stoi(value)};
                    for(int j = 1; j <= stopLoop; j++){
                        steps++;
                        if(firstWire.at(colWire).find(rowWire + j) == firstWire.at(colWire).end()){
                            firstWire.at(colWire).insert(std::make_pair(rowWire + j, steps));
                        }
                    }
                    rowWire += stopLoop;
                    value.clear();
                    i++;
                }
                else if(s[i] == 'D'){
                    int index{i + 1};
                    while(s[index] > 47 && s[index] < 58){
                        value += s[index];
                        index++;
                    }
                    int stopLoop{std::stoi(value)};
                    for(int j = 1; j <= stopLoop; j++){
                        steps++;
                        if(firstWire.at(colWire).find(rowWire - j) == firstWire.at(colWire).end()){
                            firstWire.at(colWire).insert(std::make_pair(rowWire - j, steps));
                        }
                    }
                    rowWire -= stopLoop;
                    value.clear();
                    i++;
                }
            }
            secondWire = true;
        }
        else{
            int colWire{0};
            int rowWire{0};
            int steps{0};
            std::string value;
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] == 'R'){
                    int index{i + 1};
                    while(s[index] > 47 && s[index] < 58){
                        value += s[index];
                        index++;
                    }
                    int stopLoop{std::stoi(value)};
                    for(int j = 1; j <= stopLoop; j++){
                        steps++;
                        if(firstWire.find(colWire + j) != firstWire.end() && firstWire.at(colWire + j).find(rowWire) != firstWire.at(colWire + j).end()){
                            if(res == 0 || steps + firstWire.at(colWire + j).at(rowWire) < res){
                                res = steps + firstWire.at(colWire + j).at(rowWire);
                            }
                        }
                    }
                    colWire += stopLoop;
                    value.clear();
                    i++;
                }
                else if(s[i] == 'L'){
                    int index{i + 1};
                    while(s[index] > 47 && s[index] < 58){
                        value += s[index];
                        index++;
                    }
                    int stopLoop{std::stoi(value)};
                    for(int j = 1; j <= stopLoop; j++){
                        steps++;                          // on ajoute les déplacements dans tous les cas
                        if(firstWire.find(colWire - j) != firstWire.end() && firstWire.at(colWire - j).find(rowWire) != firstWire.at(colWire - j).end()){
                            if(res == 0 || steps + firstWire.at(colWire - j).at(rowWire) < res){
                                res = steps + firstWire.at(colWire - j).at(rowWire);
                            }
                        }
                    }
                    colWire -= stopLoop;
                    value.clear();
                    i++;
                }
                else if(s[i] == 'U'){
                    int index{i + 1};
                    while(s[index] > 47 && s[index] < 58){
                        value += s[index];
                        index++;
                    }
                    int stopLoop{std::stoi(value)};                  
                    for(int j = 1; j <= stopLoop; j++){
                        steps++;
                        if(firstWire.find(colWire) != firstWire.end()){
                            if(firstWire.at(colWire).find(rowWire + j) != firstWire.at(colWire).end()){
                                if(res == 0 || steps + firstWire.at(colWire).at(rowWire + j) < res){
                                    res = steps + firstWire.at(colWire).at(rowWire + j);
                                }
                            }
                        }
                    }
                    rowWire += stopLoop;
                    value.clear();
                    i++;
                }
                else if(s[i] == 'D'){
                    int index{i + 1};
                    while(s[index] > 47 && s[index] < 58){
                        value += s[index];
                        index++;
                    }
                    int stopLoop{std::stoi(value)};
                    for(int j = 1; j <= stopLoop; j++){
                        steps++;
                        if(firstWire.find(colWire) != firstWire.end()){
                            if(firstWire.at(colWire).find(rowWire - j) != firstWire.at(colWire).end()){
                                if(res == 0 || steps + firstWire.at(colWire).at(rowWire - j) < res){
                                    res = steps + firstWire.at(colWire).at(rowWire - j);
                                }
                            }
                        }
                    }
                    rowWire -= stopLoop;
                    value.clear();
                    i++;
                }
            }
        }
    }
    std::cout << res << "\n";
    return res;
}