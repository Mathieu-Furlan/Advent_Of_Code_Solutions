#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

int main(){
    char ch;
    int res{1};
    int posLign{0};
    int posCol{0};
    std::unordered_map<int, std::unordered_set<int>> visited; // une hashMap avec les lignes comme clés et les colonnes dans un hashSet comme valeur 
    std::unordered_set<int> startSet;
    startSet.insert(0);
    visited.insert(std::make_pair(0, startSet));
    std::fstream fin("input", std::fstream::in);
    while(fin >> std::noskipws >> ch){
        if(ch == '<'){
            posCol--;
            if(visited.at(posLign).find(posCol) == visited.at(posLign).end()){
                visited.at(posLign).insert(posCol);
                res++;
            }
        }
        else if(ch == '>'){
            posCol++;
            if(visited.at(posLign).find(posCol) == visited.at(posLign).end()){
                visited.at(posLign).insert(posCol);
                res++;
            }
        }
        else if(ch == '^'){
            posLign++;
            if(visited.find(posLign) != visited.end()){
                if(visited.at(posLign).find(posCol) == visited.at(posLign).end()){
                    visited.at(posLign).insert(posCol);
                    res++;
                }
            }
            else{
                std::unordered_set<int> tempSet;
                tempSet.insert(posCol);
                visited.insert(std::make_pair(posLign, tempSet));
                res++;
            }
        }
        else if(ch == 'v'){
            posLign--;
            if(visited.find(posLign) != visited.end()){
                if(visited.at(posLign).find(posCol) == visited.at(posLign).end()){
                    visited.at(posLign).insert(posCol);
                    res++;
                }
            }
            else{
                std::unordered_set<int> tempSet;
                tempSet.insert(posCol);
                visited.insert(std::make_pair(posLign, tempSet));
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}