#include <iostream>
#include <unordered_map>

//la fonction findNeighbors trouve tous les éléments de la matrice qui s'additionnent pour former l'élément suivant
int findNeighbors(std::unordered_map<int, std::unordered_map<int, int>>& matrixPopulation, int prevCol, int prevLign){
    int val{0};
    if(matrixPopulation.find(prevCol - 1) != matrixPopulation.end()){
        if(matrixPopulation.at(prevCol - 1).find(prevLign) != matrixPopulation.at(prevCol - 1).end()){
            val += matrixPopulation.at(prevCol - 1).at(prevLign);
        }
        if(matrixPopulation.at(prevCol - 1).find(prevLign - 1) != matrixPopulation.at(prevCol - 1).end()){
            val += matrixPopulation.at(prevCol - 1).at(prevLign - 1);
        }
        if(matrixPopulation.at(prevCol - 1).find(prevLign + 1) != matrixPopulation.at(prevCol - 1).end()){
            val += matrixPopulation.at(prevCol - 1).at(prevLign + 1);
        }
    }
    if(matrixPopulation.find(prevCol) != matrixPopulation.end()){
        if(matrixPopulation.at(prevCol).find(prevLign - 1) != matrixPopulation.at(prevCol).end()){
            val += matrixPopulation.at(prevCol).at(prevLign - 1);
        }
        if(matrixPopulation.at(prevCol).find(prevLign + 1) != matrixPopulation.at(prevCol).end()){
            val += matrixPopulation.at(prevCol).at(prevLign + 1);
        }
    }
    if(matrixPopulation.find(prevCol + 1) != matrixPopulation.end()){
        if(matrixPopulation.at(prevCol + 1).find(prevLign) != matrixPopulation.at(prevCol + 1).end()){
            val += matrixPopulation.at(prevCol + 1).at(prevLign);
        }
        if(matrixPopulation.at(prevCol + 1).find(prevLign - 1) != matrixPopulation.at(prevCol + 1).end()){
            val += matrixPopulation.at(prevCol + 1).at(prevLign - 1);
        }
        if(matrixPopulation.at(prevCol + 1).find(prevLign + 1) != matrixPopulation.at(prevCol + 1).end()){
            val += matrixPopulation.at(prevCol + 1).at(prevLign + 1);
        }
    }
    if(val > 347991){
        std::cout << val << "\n";
    }
    return val;
}

int main(){
    std::unordered_map<int, std::unordered_map<int, int>> matrixPopulation;
    std::unordered_map<int, int> init;
    init.insert(std::make_pair(0, 1));
    matrixPopulation.insert(std::make_pair(0, init));
    int circleElems{8};
    int prevLign{0};
    int prevCol{0};
    bool continueLoop{true};
    while(continueLoop){
        prevCol++;
        std::unordered_map<int, int> populateMatrix;
        matrixPopulation.insert(std::make_pair(prevCol, populateMatrix));
        for(int i = 0; i < circleElems / 4; i++){
            int toBeInserted{findNeighbors(matrixPopulation, prevCol, prevLign)};
            std::cout << toBeInserted << "\n";
            if(toBeInserted > 347991){
                std::cout << toBeInserted << "\n";
                continueLoop = false;
            }
            matrixPopulation.at(prevCol).insert(std::make_pair(prevLign, toBeInserted));
            prevLign--;
        }
        prevLign++;
        prevCol--;
        for(int i = 0; i < circleElems / 4; i++){
            if(i == circleElems / 4 - 1){                              // crée une colonne tout à gauche de la matrice
                matrixPopulation.insert(std::make_pair(prevCol, populateMatrix));
            }
            int toBeInserted{findNeighbors(matrixPopulation, prevCol, prevLign)};
            std::cout << toBeInserted << "\n";
            if(toBeInserted > 347991){
                std::cout << toBeInserted << "\n";
                continueLoop = false;
            }
            matrixPopulation.at(prevCol).insert(std::make_pair(prevLign, toBeInserted));
            prevCol--;
        }
        prevCol++;
        prevLign++;
        for(int i = 0; i < circleElems / 4; i++){
            int toBeInserted{findNeighbors(matrixPopulation, prevCol, prevLign)};
            std::cout << toBeInserted << "\n";
            if(toBeInserted > 347991){
                std::cout << toBeInserted << "\n";
                continueLoop = false;
            }
            matrixPopulation.at(prevCol).insert(std::make_pair(prevLign, toBeInserted));
            prevLign++;
        }
        prevLign--;
        prevCol++;
        for(int i = 0; i < circleElems / 4; i++){
            int toBeInserted{findNeighbors(matrixPopulation, prevCol, prevLign)};
            std::cout << toBeInserted << "\n";
            if(toBeInserted > 347991){
                std::cout << toBeInserted << "\n";
                continueLoop = false;
            }
            matrixPopulation.at(prevCol).insert(std::make_pair(prevLign, toBeInserted));
            prevCol++;
        }
        prevCol--;
        circleElems += 8;
    }
    return 0;
}