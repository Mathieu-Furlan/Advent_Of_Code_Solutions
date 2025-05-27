#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <set>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<int, std::set<int>> occupationCol;
    int lowestRow{0};
    while(getline(file, s)){
        bool lignCol{true};
        bool prevCreated{false};
        int counter{0};
        int colEnd{-1};
        int lignEnd{-1};
        int prevCol;
        int prevLign;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58 && lignCol){
                int index{i};
                std::string colConstructor;
                while(s[index] > 47 && s[index] < 58){
                    colConstructor += s[index];
                    index++;
                    i++;
                }
                colEnd = std::stoi(colConstructor);
                lignCol = false;
                counter++;
            }
            else if(s[i] > 47 && s[i] < 58 && !lignCol){
                int index{i};
                std::string lignConstructor;
                while(s[index] > 47 && s[index] < 58){
                    lignConstructor += s[index];
                    index++;
                    i++;
                }
                lignEnd = std::stoi(lignConstructor);
                if(lignEnd > lowestRow){
                    lowestRow = lignEnd;
                }
                lignCol = true;
                counter++;
                if(prevCreated){
                    if(prevLign == lignEnd){
                        if(prevCol < colEnd){
                            for(int j = prevCol; j <= colEnd; j++){
                                if(occupationCol.find(j) != occupationCol.end()){
                                    occupationCol.at(j).insert(lignEnd);
                                }
                                else{
                                    std::set<int> tempSet;
                                    tempSet.insert(lignEnd);
                                    occupationCol.insert(std::make_pair(j, tempSet));
                                }
                            }
                        }
                        else{
                            for(int j = colEnd; j <= prevCol; j++){
                                if(occupationCol.find(j) != occupationCol.end()){
                                    occupationCol.at(j).insert(lignEnd);
                                }
                                else{
                                    std::set<int> tempSet;
                                    tempSet.insert(lignEnd);
                                    occupationCol.insert(std::make_pair(j, tempSet));
                                }
                            }
                        }
                    }
                    else if(prevCol == colEnd){
                        if(occupationCol.find(colEnd) == occupationCol.end()){
                            std::set<int> tempSet;
                            occupationCol.insert(std::make_pair(colEnd, tempSet));
                        }
                        if(prevLign < lignEnd){
                            for(int j = prevLign; j <= lignEnd; j++){
                                occupationCol.at(colEnd).insert(j);
                            }
                        }
                        else{
                            for(int j = lignEnd; j <= prevLign; j++){
                                occupationCol.at(colEnd).insert(j);
                            }
                        }
                    }
                }
                else prevCreated = true;
                prevCol = colEnd;
                prevLign = lignEnd;
            }
        }
    }
    lowestRow += 2;
    for(auto& [col, rows] : occupationCol){
        rows.insert(lowestRow);
    }
    bool sourceBlocked{false};
    int res{0};
    while(!sourceBlocked){
        int elevation{0};
        int colSand{500};
        bool sandRest{false};
        while(!sandRest){
            if(occupationCol.find(colSand) == occupationCol.end()){   // si il n'y a rien dans la colonne on ajoute le niveau minimal
                std::set<int> tempSet;
                tempSet.insert(lowestRow);
                tempSet.insert(lowestRow - 1);
                std::cout << "colSand " << colSand << "\n";
                std::cout << "elevation " << lowestRow + 1 << "\n";
                occupationCol.insert(std::make_pair(colSand, tempSet));
                sandRest = true;
                continue;
            }
            for(auto& rocks : occupationCol.at(colSand)){
                if(rocks > elevation){      // si on trouve un élément plus bas que le sable
                    elevation = rocks - 1;
                    if(elevation < lowestRow - 1 && (occupationCol.find(colSand - 1) == occupationCol.end() || occupationCol.at(colSand - 1).find(elevation + 1) == occupationCol.at(colSand - 1).end())){
                        colSand--;          // on regarde si on peut aller à gauche
                        elevation++;
                    }
                    else if(elevation < lowestRow - 1 && (occupationCol.find(colSand + 1) == occupationCol.end() || occupationCol.at(colSand + 1).find(elevation + 1) == occupationCol.at(colSand + 1).end())){
                        colSand++;          // on regarde si on peut aller à droite
                        elevation++;
                    }
                    else{
                        std::cout << "colSand " << colSand << "\n";
                        std::cout << "elevation " << elevation << "\n";
                        occupationCol.at(colSand).insert(elevation);
                        sandRest = true;
                    }
                    break;
                }
            }
        }
        if(sandRest){
            res++;
            if(colSand == 500 && elevation == 0){
                sourceBlocked = true;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}