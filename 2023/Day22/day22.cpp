#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<std::array<int, 2>, 3>> bricksInitial;
    while(getline(file, s)){
        std::array<int, 2> xPos;
        std::array<int, 2> yPos;
        std::array<int, 2> zPos;
        long unsigned int tilde{s.find('~', 0)};
        xPos[0] = s[0] - '0';
        yPos[0] = s[2] - '0';
        zPos[0] = std::stoi(s.substr(4, tilde - 4));
        xPos[1] = std::stoi(s.substr(tilde + 1, 1));
        yPos[1] = std::stoi(s.substr(tilde + 3, 1));
        zPos[1] = std::stoi(s.substr(tilde + 5));
        std::array<std::array<int, 2>, 3> tempBricks{{xPos, yPos, zPos}};
        bricksInitial.push_back(tempBricks);
    }                   // on trie les éléments par ordre croissant de hauteur minimale de départ
    std::sort(bricksInitial.begin(), bricksInitial.end(), [](const std::array<std::array<int, 2>, 3>& a, const std::array<std::array<int, 2>, 3>& b){
        if(a[2][0] < b[2][0]){
            return true;
        }
        else if(a[2][0] > b[2][0]){
            return false;
        }
        else return true;
    });
    std::vector<std::array<std::array<std::string, 10>, 10>> brickStack;
    std::array<std::string, 10> groundInit;
    std::array<std::string, 10> levelInit;
    std::fill(groundInit.begin(), groundInit.end(), "ground");
    std::fill(levelInit.begin(), levelInit.end(), ".");
    std::array<std::array<std::string, 10>, 10> groundRow;
    std::array<std::array<std::string, 10>, 10> levelStack;
    for(int i = 0; i < 10; i++){
        groundRow[i] = groundInit;
        levelStack[i] = levelInit;
    }
    brickStack.push_back(groundRow);           // le niveau 0
    brickStack.push_back(levelStack);          // le niveau 1
    int brickNumber{0};                        // le numéro des éléments pour les distinguer
    std::unordered_map<int, std::vector<std::string>> blockingElements;
    std::unordered_set<std::string> disintegrated;
    for(auto& brickCluster : bricksInitial){
        if(brickNumber <= 25){                          // imprime l'état des premiers niveaux dans le terminal
            for(auto& stackLevel : brickStack){
                std::cout << "level" << "\n";
                for(int i = 0; i <= stackLevel.size() - 1; i++){
                    for(int j = 0; j <= stackLevel[i].size() - 1; j++){
                        std::cout << stackLevel[i][j];
                    }
                    std::cout << "\n";
                }
            }
        }
        bool blocked{false};
        int fallHeight{0};
        while(brickStack.size() - 1 < brickCluster[2][0]){
            brickStack.push_back(levelStack);
        }
        while(!blocked){
            int currentLevel{brickCluster[2][0] - 1 - fallHeight};       // on regarde si l'élément est bloqué en commençant par le niveau juste en dessous de sa base
            for(int i = brickCluster[0][0]; i <= brickCluster[0][1]; i++){     // on vérifie si l'élément est bloqué sur l'axe X
                if(brickStack[currentLevel][i][brickCluster[1][0]] != "."){
                    if(blockingElements.size() == 0 || blockingElements.find(brickNumber) == blockingElements.end()){
                        std::vector<std::string> initMapValue;       // une hashmap qui contient les éléments qui soutiennent l'élément qui est la clé de l'hashmap
                        initMapValue.push_back(brickStack[currentLevel][i][brickCluster[1][0]]);
                        blockingElements.insert(std::make_pair(brickNumber, initMapValue));
                    }
                    else if(std::find(blockingElements.at(brickNumber).begin(), blockingElements.at(brickNumber).end(), brickStack[currentLevel][i][brickCluster[1][0]]) == blockingElements.at(brickNumber).end()){
                        blockingElements.at(brickNumber).push_back(brickStack[currentLevel][i][brickCluster[1][0]]);
                    }
                    blocked = true;
                }
            }
            for(int i = brickCluster[1][0]; i <= brickCluster[1][1]; i++){      // on vérifie si l'élément est bloqué sur l'axe Y
                if(brickStack[currentLevel][brickCluster[0][0]][i] != "."){
                    if(blockingElements.size() == 0 || blockingElements.find(brickNumber) == blockingElements.end()){
                        std::vector<std::string> initMapValue;
                        initMapValue.push_back(brickStack[currentLevel][brickCluster[0][0]][i]);
                        blockingElements.insert(std::make_pair(brickNumber, initMapValue));
                    }
                    else if(std::find(blockingElements.at(brickNumber).begin(), blockingElements.at(brickNumber).end(), brickStack[currentLevel][brickCluster[0][0]][i]) == blockingElements.at(brickNumber).end()){
                        blockingElements.at(brickNumber).push_back(brickStack[currentLevel][brickCluster[0][0]][i]);
                    }
                    blocked = true;
                }
            }
            if(blocked){
                int verticalElevation{1};
                while(verticalElevation <= brickCluster[2][1] - (brickCluster[2][0] - 1)){
                    if(verticalElevation + currentLevel == brickStack.size()){          // si le niveau n'existe pas on le crée
                        brickStack.push_back(levelStack);
                    }
                    for(int i = brickCluster[0][0]; i <= brickCluster[0][1]; i++){     // on ajoute les blocs sur l'axe X
                        brickStack[currentLevel + verticalElevation][i][brickCluster[1][0]] = std::to_string(brickNumber);  // le nom de l'élément pour les distinguer
                    }
                    for(int i = brickCluster[1][0]; i <= brickCluster[1][1]; i++){      // on ajoute les blocs sur l'axe Y
                        brickStack[currentLevel + verticalElevation][brickCluster[0][0]][i] = std::to_string(brickNumber);
                    }
                    verticalElevation++;
                }
            }
            fallHeight++;    // si l'élément n'est pas bloqué au niveau actuel il continue de tomber
            disintegrated.insert(std::to_string(brickNumber));      // on ajoute tous les éléments dans un set
        }
        brickNumber++;
    }
    for(auto& [key, val] : blockingElements){
        if(val.size() == 1){          // si un élément est bloqué par un seul autre on ne peut pas le supprimer
            if(disintegrated.find(val[0]) != disintegrated.end()){
                disintegrated.erase(val[0]);
            }
        }
    }
    std::cout << disintegrated.size() << "\n";  // le résultat est la taille du set après les suppressions
    return 0;
}