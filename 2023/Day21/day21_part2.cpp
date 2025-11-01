#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <cmath>

/*
    il y a 65 pas à partir de S vers le haut, le bas, la gauche et la droite;
    pour trouver le nombre de parcelles qu'il est possible d'atteindre en 65 + 2 * 131 pas il faut reproduire la matrice 5 fois à gauche et à droite et 5 * 11 fois au dessus et en dessous
*/
void bfsCore(std::queue<std::array<int, 2>>& queuePath, int elemNumber, std::array<std::array<char, 1441>, 1441> matrix, std::vector<std::array<int, 2>>& pathPos){
    for(int i = 0; i < pathPos.size(); i++){
        matrix[pathPos[i][0]][pathPos[i][1]] = 35;
    }
    pathPos.clear();
    while(elemNumber > 0){
        int currLign{queuePath.front()[0]};
        int currCol{queuePath.front()[1]};
        queuePath.pop();
        if(currLign > 0 && matrix[currLign - 1][currCol] == '.'){
            queuePath.push({currLign - 1, currCol});
            pathPos.push_back({currLign - 1, currCol});
            matrix[currLign - 1][currCol] = 35;
        }
        if(currLign < matrix.size() - 1 && matrix[currLign + 1][currCol] == '.'){
            queuePath.push({currLign + 1, currCol});
            pathPos.push_back({currLign + 1, currCol});
            matrix[currLign + 1][currCol] = 35;
        }
        if(currCol < matrix[0].size() - 1 && matrix[currLign][currCol + 1] == '.'){
            queuePath.push({currLign, currCol + 1});
            pathPos.push_back({currLign, currCol + 1});
            matrix[currLign][currCol + 1] = 35;
        }
        if(currCol > 0 && matrix[currLign][currCol - 1] == '.'){
            queuePath.push({currLign, currCol - 1});
            pathPos.push_back({currLign, currCol - 1});
            matrix[currLign][currCol - 1] = 35;
        }
        elemNumber--;
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::array<std::array<char, 1441>, 1441> matrix;
    int lineCounter{0};
    while(getline(file, s)){
        int padStart{0};
        for(int i = 0; i < s.length(); i++){
            char currChar{s[i]};
            if(s[i] == 'S'){
                currChar = 46;
            }
            for(int j = 0 + lineCounter; j < matrix.size(); j = j + 131){
                for(int k = 0 + padStart; k < matrix[j].size(); k = k + 131){
                    matrix[j][k] = currChar;
                }
            }
            padStart++;
        }
        lineCounter++;
    }
    int totalSteps{65};
    std::array<long unsigned, 3> plotsReachable;
    for(int i = 0; i < 3; i++){
        std::queue<std::array<int, 2>> queuePath;
        std::vector<std::array<int, 2>> temporaryPos;
        queuePath.push({720, 720});
        temporaryPos.push_back({720, 720});
        int elfSteps{0};
        while(elfSteps < totalSteps && !queuePath.empty()){
            long unsigned elemNumber{queuePath.size()};
            elfSteps++;
            bfsCore(queuePath, elemNumber, matrix, temporaryPos);
        }
        totalSteps += 131;
        plotsReachable[i] = queuePath.size();
        std::cout << queuePath.size() << "\n";
    }
    long unsigned r1{plotsReachable[0]};
    long unsigned r2{plotsReachable[1]};
    long unsigned r3{plotsReachable[2]};
    long unsigned unknownA{(r3 + r1 - 2 * r2) / 2};
    long unsigned unknownB{r2 - r1 - unknownA};
    long double unknownC{(double)r1};
    long double res{unknownA * std::pow(202300, 2) + unknownB * 202300 + unknownC};             // ax² + bx + c
    std::cout.precision(25);
    std::cout << res << "\n";
    return 0;
}