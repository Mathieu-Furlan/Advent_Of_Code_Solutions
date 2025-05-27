#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<std::vector<char>> detailsEnhancing(std::vector<std::vector<char>>& inputImage, int repetitions, std::vector<std::array<std::array<char, 2>, 2>>& sizeTwoGrids, std::vector<std::array<std::array<char, 3>, 3>>& sizeTwoRules, std::vector<std::array<std::array<char, 3>, 3>>& sizeThreeGrids, std::vector<std::array<std::array<char, 4>, 4>>& sizeThreeRules){
    if(repetitions == 0){
        return inputImage;
    }
    std::vector<std::vector<char>> outputPattern;
    if(inputImage.size() % 2 == 0){
        unsigned long outputSize{inputImage.size() + inputImage.size() / 2};
        for(int m = 0; m <= outputSize - 1; m++){
            std::vector<char> init;
            outputPattern.push_back(init);
        }
        std::vector<std::array<std::array<char, 2>, 2>> gridDivisions;
        for(int i = 0; i < inputImage.size(); i = i + 2){      // pour chaque rectangle de dimension 2 x (inputPattern.size() / 2)
            for(int j = 0; j < inputImage.size(); j = j + 2){   // pour chaque carré de dimension 2 x 2
                std::array<std::array<char, 2>, 2> tempDiv;
                int startRow{i};
                int startCol{j};
                int populateRow{0};
                int populateCol{0};
                for(int k = i; k < i + 2; k++){                 // pour chaque ligne du carré de 2 x 2
                    for(int m = j; m < j + 2; m++){                 // pour chaque élément de chaque ligne
                        tempDiv[populateRow][populateCol] = inputImage[k][m];
                        populateCol++;
                    }
                    populateRow++;
                    populateCol = 0;
                }
                gridDivisions.push_back(tempDiv);
            }
        }
        int populateMatrixRow{0};
        int populateMatrixCol{0};
        std::array<std::array<std::array<char, 2>, 2>, 8> rotateAndFlip;
        for(auto& individualDivided : gridDivisions){
            rotateAndFlip[0] = individualDivided;                                       // le schéma de départ
            std::array<std::array<char, 2>, 2> reversedOriginal{individualDivided};
            for(int k = 0; k < 2; k++){
                std::reverse(reversedOriginal[k].begin(), reversedOriginal[k].end());
            }
            rotateAndFlip[1] = reversedOriginal;                                        // le schéma de départ inversé
            std::array<std::array<char, 2>, 2> rotated180;
            int moveRow{1};
            for(int k = 0; k < 2; k++){
                rotated180[k] = individualDivided[moveRow];
                moveRow--;
            }
            rotateAndFlip[2] = rotated180;                                              // rotation de 180 degrés
            std::array<std::array<char, 2>, 2> reversed180{rotated180};
            for(int k = 0; k < 2; k++){
                std::reverse(reversed180[k].begin(), reversed180[k].end());
            }
            rotateAndFlip[3] = reversed180;                                             // 180 degrés inversés
            std::array<std::array<char, 2>, 2> rotated90Left;
            for(int m = 0; m < 2; m++){
                int reversedCounter{1};
                for(int k = 0; k < 2; k++){
                    rotated90Left[m][k] = individualDivided[reversedCounter][m];
                    reversedCounter--;
                }
            }
            rotateAndFlip[4] = rotated90Left;                                           // 90 degrés gauche
            std::array<std::array<char, 2>, 2> reversed90Left{rotated90Left};
            for(int k = 0; k < 2; k++){
                std::reverse(reversed90Left[k].begin(), reversed90Left[k].end());
            }
            rotateAndFlip[5] = reversed90Left;                                          // 90 degrés gauche inversé
            std::array<std::array<char, 2>, 2> rotated90Right;
            int remoteCounter{1};
            for(int m = 0; m < 2; m++){
                for(int k = 0; k < 2; k++){
                    rotated90Right[m][k] = individualDivided[k][remoteCounter];
                }
                remoteCounter--;
            }
            rotateAndFlip[6] = rotated90Right;                                           // 90 degrés droite
            std::array<std::array<char, 2>, 2> reversed90Right{rotated90Right};
            for(int k = 0; k < 2; k++){
                std::reverse(reversed90Right[k].begin(), reversed90Right[k].end());
            }
            rotateAndFlip[7] = reversed90Right;                                         // 90 degrés droite inversé
            bool patternFound{false};
            int ruleIndex{0};
            for(int k = 0; k <= sizeTwoGrids.size() - 1; k++){
                for(auto& rotatedFlipped : rotateAndFlip){
                    if(rotatedFlipped == sizeTwoGrids[k]){
                        ruleIndex = k;
                        patternFound = true;
                        break;
                    }
                }
                if(patternFound){
                    break;
                }
            }
            int selectRow{0};
            int selectCol{0};
            for(int i = populateMatrixRow; i <= populateMatrixRow + 2; i++){
                for(int j = populateMatrixCol; j <= populateMatrixCol + 2; j++){
                    outputPattern[i].push_back(sizeTwoRules[ruleIndex][selectRow][selectCol]);
                    selectCol++;
                }
                selectRow++;
                selectCol = 0;     
            }
            populateMatrixCol += 3;
            if(populateMatrixCol == outputSize){
                populateMatrixRow += 3;
                populateMatrixCol = 0;
            }
        }
    }
    else if(inputImage.size() % 3 == 0){
        unsigned long outputSize{inputImage.size() + inputImage.size() / 3};
        for(int m = 0; m <= outputSize - 1; m++){
            std::vector<char> init;
            outputPattern.push_back(init);
        }
        std::vector<std::array<std::array<char, 3>, 3>> gridDivisions;
        for(int i = 0; i < inputImage.size(); i = i + 3){      // pour chaque rectangle de dimension 3 x (inputPattern.size() / 3)
            for(int j = 0; j < inputImage.size(); j = j + 3){   // pour chaque carré de dimension 3 x 3
                std::array<std::array<char, 3>, 3> tempDiv;
                int startRow{i};
                int startCol{j};
                int populateRow{0};
                int populateCol{0};
                for(int k = i; k < i + 3; k++){                 // pour chaque ligne du carré de 3 x 3
                    for(int m = j; m < j + 3; m++){                 // pour chaque élément de chaque ligne
                        tempDiv[populateRow][populateCol] = inputImage[k][m];
                        populateCol++;
                    }
                    populateRow++;
                    populateCol = 0;
                }
                gridDivisions.push_back(tempDiv);
            }
        }
        int populateMatrixRow{0};
        int populateMatrixCol{0};
        std::array<std::array<std::array<char, 3>, 3>, 8> rotateAndFlip;
        for(auto& individualDivided : gridDivisions){
            rotateAndFlip[0] = individualDivided;                                       // le schéma de départ
            std::array<std::array<char, 3>, 3> reversedOriginal{individualDivided};
            for(int k = 0; k < 3; k++){
                std::reverse(reversedOriginal[k].begin(), reversedOriginal[k].end());
            }
            rotateAndFlip[1] = reversedOriginal;                                        // le schéma de départ inversé
            std::array<std::array<char, 3>, 3> rotated180;
            int moveRow{2};
            for(int k = 0; k < 3; k++){
                rotated180[k] = individualDivided[moveRow];
                moveRow--;
            }
            rotateAndFlip[2] = rotated180;                                              // rotation de 180 degrés
            std::array<std::array<char, 3>, 3> reversed180{rotated180};
            for(int k = 0; k < 3; k++){
                std::reverse(reversed180[k].begin(), reversed180[k].end());
            }
            rotateAndFlip[3] = reversed180;                                             // 180 degrés inversés
            std::array<std::array<char, 3>, 3> rotated90Left;
            for(int m = 0; m < 3; m++){
                int reversedCounter{2};
                for(int k = 0; k < 3; k++){
                    rotated90Left[reversedCounter][m] = individualDivided[m][k];
                    reversedCounter--;
                }
            }
            rotateAndFlip[4] = rotated90Left;                                           // 90 degrés gauche
            std::array<std::array<char, 3>, 3> reversed90Left{rotated90Left};
            for(int k = 0; k < 3; k++){
                std::reverse(reversed90Left[k].begin(), reversed90Left[k].end());
            }
            rotateAndFlip[5] = reversed90Left;                                          // 90 degrés gauche inversé
            std::array<std::array<char, 3>, 3> rotated90Right;
            int remoteCounter{2};
            for(int m = 0; m < 3; m++){
                for(int k = 0; k < 3; k++){
                    rotated90Right[k][m] = individualDivided[remoteCounter][k];
                }
                remoteCounter--;
            }
            rotateAndFlip[6] = rotated90Right;                                           // 90 degrés droite
            std::array<std::array<char, 3>, 3> reversed90Right{rotated90Right};
            for(int k = 0; k < 3; k++){
                std::reverse(reversed90Right[k].begin(), reversed90Right[k].end());
            }
            rotateAndFlip[7] = reversed90Right;                                         // 90 degrés droite inversé
            bool patternFound{false};
            int ruleIndex{0};
            for(int k = 0; k <= sizeThreeGrids.size() - 1; k++){
                for(auto& rotatedFlipped : rotateAndFlip){
                    if(rotatedFlipped == sizeThreeGrids[k]){
                        ruleIndex = k;
                        patternFound = true;
                        break;
                    }
                }
                if(patternFound){
                    break;
                }
            }
            int selectRow{0};
            int selectCol{0};
            for(int i = populateMatrixRow; i <= populateMatrixRow + 3; i++){
                for(int j = populateMatrixCol; j <= populateMatrixCol + 3; j++){
                    outputPattern[i].push_back(sizeThreeRules[ruleIndex][selectRow][selectCol]);
                    selectCol++;
                }
                selectRow++;
                selectCol = 0;
            }
            populateMatrixCol += 4;
            if(populateMatrixCol == outputSize){
                populateMatrixRow += 4;
                populateMatrixCol = 0;
            }
        }
    }
    return detailsEnhancing(outputPattern, repetitions - 1, sizeTwoGrids, sizeTwoRules, sizeThreeGrids, sizeThreeRules);
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<std::array<char, 2>, 2>> sizeTwoGrids;
    std::vector<std::array<std::array<char, 3>, 3>> sizeTwoRules;
    std::vector<std::array<std::array<char, 3>, 3>> sizeThreeGrids;
    std::vector<std::array<std::array<char, 4>, 4>> sizeThreeRules;
    std::vector<std::vector<char>> inputPattern{{{'.', '#', '.'}, {'.', '.', '#'}, {'#', '#', '#'}}};
    while(getline(file, s)){
        if(s[6] == '='){
            sizeTwoGrids.push_back({{{s[0], s[1]}, {s[3], s[4]}}});
            sizeTwoRules.push_back({{{s[9], s[10], s[11]}, {s[13], s[14], s[15]}, {s[17], s[18], s[19]}}});
        }
        else if(s[12] == '='){
            sizeThreeGrids.push_back({{{s[0], s[1], s[2]}, {s[4], s[5], s[6]}, {s[8], s[9], s[10]}}});
            sizeThreeRules.push_back({{{s[15], s[16], s[17], s[18]}, {s[20], s[21], s[22], s[23]}, {s[25], s[26], s[27], s[28]}, {s[30], s[31], s[32], s[33]}}});
        }
    }
    int res{0};
    std::vector<std::vector<char>> outputImage = detailsEnhancing(inputPattern, 18, sizeTwoGrids, sizeTwoRules, sizeThreeGrids, sizeThreeRules);
    for(int i = 0; i <= outputImage.size() - 1; i++){
        for(int j = 0; j <= outputImage[0].size() - 1; j++){
            if(outputImage[i][j] == '#'){
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return 0;
}