#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<int, std::unordered_set<int>> firstWire;
    std::unordered_map<int, std::unordered_set<int>> intersectionPoints;
    std::unordered_set<int> init{0};
    firstWire.insert(std::make_pair(0, init));
    bool secondWire{false};
    while(getline(file, s)){
        if(!secondWire){
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
                        if(firstWire.find(colWire + j) == firstWire.end()){
                            std::unordered_set<int> tempSet;
                            tempSet.insert(rowWire);
                            firstWire.insert(std::make_pair(colWire + j, tempSet));
                        }
                        else firstWire.at(colWire + j).insert(rowWire);
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
                        if(firstWire.find(colWire - j) == firstWire.end()){
                            std::unordered_set<int> tempSet;
                            tempSet.insert(rowWire);
                            firstWire.insert(std::make_pair(colWire - j, tempSet));
                        }
                        else firstWire.at(colWire - j).insert(rowWire);
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
                        firstWire.at(colWire).insert(rowWire + j);
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
                        firstWire.at(colWire).insert(rowWire - j);
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
                        if(firstWire.find(colWire + j) != firstWire.end() && firstWire.at(colWire + j).find(rowWire) != firstWire.at(colWire + j).end()){
                            std::unordered_set<int> tempSet;
                            tempSet.insert(rowWire);
                            intersectionPoints.insert(std::make_pair(colWire + j, tempSet));
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
                        if(firstWire.find(colWire - j) != firstWire.end() && firstWire.at(colWire - j).find(rowWire) != firstWire.at(colWire - j).end()){
                            std::unordered_set<int> tempSet;
                            tempSet.insert(rowWire);
                            intersectionPoints.insert(std::make_pair(colWire - j, tempSet));
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
                    if(firstWire.find(colWire) != firstWire.end()){
                        for(int j = 1; j <= stopLoop; j++){
                            if(firstWire.at(colWire).find(rowWire + j) != firstWire.at(colWire).end()){
                                intersectionPoints.insert(std::make_pair(colWire, rowWire + j));
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
                    if(firstWire.find(colWire) != firstWire.end()){
                        for(int j = 1; j <= stopLoop; j++){
                            if(firstWire.at(colWire).find(rowWire - j) != firstWire.at(colWire).end()){
                                intersectionPoints.insert(std::make_pair(colWire, rowWire - j));
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
    int res{0};
    for(auto& [key, val] : intersectionPoints){
        for(auto& row : val){
            int tempCol{key};
            int tempRow{row};
            if(tempCol < 0){
                tempCol *= -1;
            }
            if(tempRow < 0){
                tempRow *= -1;
            }
            int distance = tempCol + tempRow;
            if(res == 0 || distance < res){
                res = distance;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}