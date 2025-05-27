#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::vector<char>> matrix;
    std::vector<std::vector<char>> duplicate;
    int startLign{0};
    int startColumn{0};
    int lign{0};
    while(getline(file, s)){
        std::vector<char> temp;
        for(int i = 0; i <= s.length() - 1; i++){
            temp.push_back(s[i]);
            if(s[i] == 'S'){
                startColumn = i;
                startLign = lign;
            }
        }
        matrix.push_back(temp);
        duplicate.push_back(temp);                 // duplicate conserve l'état d'origine de la matrice
        lign++;
    }
    std::array<int, 2> currPos;  
    currPos[0] = startLign;
    currPos[1] = startColumn;
    duplicate[startLign][startColumn] = '|';            // on remplace le S de départ manuellement
    while(currPos[0] != -1){
        int currLign{currPos[0]};
        int currCol{currPos[1]};
        currPos[0] = -1;
        if(currLign < matrix.size() - 1 && (matrix[currLign + 1][currCol] == '|' || matrix[currLign + 1][currCol] == 'L' || matrix[currLign + 1][currCol] == 'J') && (matrix[currLign][currCol] == '7' || matrix[currLign][currCol] == 'F' || matrix[currLign][currCol] == '|' || matrix[currLign][currCol] == 'S')){
            currPos = {currLign + 1, currCol};
        }
        else if(currLign > 0 && (matrix[currLign - 1][currCol] == '|' || matrix[currLign - 1][currCol] == '7' || matrix[currLign - 1][currCol] == 'F') && (matrix[currLign][currCol] == 'J' || matrix[currLign][currCol] == 'L' || matrix[currLign][currCol] == '|' || matrix[currLign][currCol] == 'S')){
            currPos = {currLign - 1, currCol};
        }
        else if(currCol <= matrix[0].size() - 1 && (matrix[currLign][currCol + 1] == '-' || matrix[currLign][currCol + 1] == '7' || matrix[currLign][currCol + 1] == 'J') && (matrix[currLign][currCol] == 'L' || matrix[currLign][currCol] == 'F' || matrix[currLign][currCol] == '-' || matrix[currLign][currCol] == 'S')){
            currPos = {currLign, currCol + 1};
        }
        else if(currCol > 0 && (matrix[currLign][currCol - 1] == '-' || matrix[currLign][currCol - 1] == 'F' || matrix[currLign][currCol - 1] == 'L') && (matrix[currLign][currCol] == '7' || matrix[currLign][currCol] == 'J' || matrix[currLign][currCol] == '-' || matrix[currLign][currCol] == 'S')){
            currPos = {currLign, currCol - 1};
        }
        matrix[currLign][currCol] = '#';
    }
    int area{0};
    for(int m = matrix[0].size(); m > 0; m--){   // on parcourt la matrice en diagonale en commençant par le coin supérieur droit
        int indexLign{0};
        int indexCol{m - 1};
        bool oddEven{true};           // true signifie pair;
        while(indexLign <= matrix.size() - 1 && indexCol <= matrix[0].size() - 1){
            if(matrix[indexLign][indexCol] == '#' && (duplicate[indexLign][indexCol] == '-' || duplicate[indexLign][indexCol] == '|' || duplicate[indexLign][indexCol] == 'F' || duplicate[indexLign][indexCol] == 'J')){
                if(oddEven){
                    oddEven = false;
                }
                else oddEven = true;
            }
            else if(!oddEven && matrix[indexLign][indexCol] != '#'){
                std::cout << "indexLign " << indexLign << "\n";
                std::cout << "indexCol " << indexCol<< "\n";
                area++;
            }
            indexLign++;
            indexCol++;
        }
    }
    for(int m = 1; m <= matrix.size() - 1; m++){                // coin inférieur gauche
        int indexLign{m};
        int indexCol{0};
        bool oddEven{true};           // true signifie pair;
        while(indexLign <= matrix.size() - 1 && indexCol <= matrix[0].size() - 1){
            if(matrix[indexLign][indexCol] == '#' && (duplicate[indexLign][indexCol] == '-' || duplicate[indexLign][indexCol] == '|' || duplicate[indexLign][indexCol] == 'F' || duplicate[indexLign][indexCol] == 'J')){
                if(oddEven){
                    oddEven = false;
                }
                else oddEven = true;
            }
            else if(!oddEven && matrix[indexLign][indexCol] != '#'){
                std::cout << "indexLign " << indexLign << "\n";
                std::cout << "indexCol " << indexCol<< "\n";
                area++;
            }
            indexLign++;
            indexCol++;
        }
    }
    std::cout << area << "\n";
    return 0;
}