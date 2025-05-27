#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <array>

int main(){
    char ch;
    int res{1};
    std::unordered_map<int, std::unordered_set<int>> visited;
    std::unordered_set<int> startSet;
    startSet.insert(0);
    visited.insert(std::make_pair(0, startSet));
    std::array<int, 2> entityA{{0, 0}};
    std::array<int, 2> entityB{{0, 0}};
    int takeTurn{-1};
    std::fstream fin("input", std::fstream::in);
    while(fin >> std::noskipws >> ch){
        takeTurn++;
        if(takeTurn % 2 == 0){
            if(ch == '<'){
                entityA[1]--;
                if(visited.at(entityA[0]).find(entityA[1]) == visited.at(entityA[0]).end()){
                    visited.at(entityA[0]).insert(entityA[1]);
                    res++;
                }
            }
            else if(ch == '>'){
                entityA[1]++;
                if(visited.at(entityA[0]).find(entityA[1]) == visited.at(entityA[0]).end()){
                    visited.at(entityA[0]).insert(entityA[1]);
                    res++;
                }
            }
            else if(ch == '^'){
                entityA[0]++;
                if(visited.find(entityA[0]) != visited.end()){
                    if(visited.at(entityA[0]).find(entityA[1]) == visited.at(entityA[0]).end()){
                        visited.at(entityA[0]).insert(entityA[1]);
                        res++;
                    }
                }
                else{
                    std::unordered_set<int> tempSet;
                    tempSet.insert(entityA[1]);
                    visited.insert(std::make_pair(entityA[0], tempSet));
                    res++;
                }
            }
            else if(ch == 'v'){
                entityA[0]--;
                if(visited.find(entityA[0]) != visited.end()){
                    if(visited.at(entityA[0]).find(entityA[1]) == visited.at(entityA[0]).end()){
                        visited.at(entityA[0]).insert(entityA[1]);
                        res++;
                    }
                }
                else{
                    std::unordered_set<int> tempSet;
                    tempSet.insert(entityA[1]);
                    visited.insert(std::make_pair(entityA[0], tempSet));
                    res++;
                }
            }
        }
        else{
            if(ch == '<'){
                entityB[1]--;
                if(visited.at(entityB[0]).find(entityB[1]) == visited.at(entityB[0]).end()){
                    visited.at(entityB[0]).insert(entityB[1]);
                    res++;
                }
            }
            else if(ch == '>'){
                entityB[1]++;
                if(visited.at(entityB[0]).find(entityB[1]) == visited.at(entityB[0]).end()){
                    visited.at(entityB[0]).insert(entityB[1]);
                    res++;
                }
            }
            else if(ch == '^'){
                entityB[0]++;
                if(visited.find(entityB[0]) != visited.end()){
                    if(visited.at(entityB[0]).find(entityB[1]) == visited.at(entityB[0]).end()){
                        visited.at(entityB[0]).insert(entityB[1]);
                        res++;
                    }
                }
                else{
                    std::unordered_set<int> tempSet;
                    tempSet.insert(entityB[1]);
                    visited.insert(std::make_pair(entityB[0], tempSet));
                    res++;
                }
            }
            else if(ch == 'v'){
                entityB[0]--;
                if(visited.find(entityB[0]) != visited.end()){
                    if(visited.at(entityB[0]).find(entityB[1]) == visited.at(entityB[0]).end()){
                        visited.at(entityB[0]).insert(entityB[1]);
                        res++;
                    }
                }
                else{
                    std::unordered_set<int> tempSet;
                    tempSet.insert(entityB[1]);
                    visited.insert(std::make_pair(entityB[0], tempSet));
                    res++;
                }
            }
        }
    }
    std::cout << res << "\n";
    return res;
}