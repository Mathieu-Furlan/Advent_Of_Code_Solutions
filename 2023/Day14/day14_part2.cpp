#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::vector<char>> matrix;
    while(getline(file, s)){
        std::vector<char> temp;
        for(int i = 0; i <= s.length() - 1; i++){
            temp.push_back(s[i]);
        }
        matrix.push_back(temp);
    }
    int cycles{0};
    int startLoop{0};
    std::vector<std::string> pastStates;              // utiliser vector car unordered_set ne retourne pas les éléments dans l'ordre d'insertion
    bool repeatState{false};
    while(!repeatState){
        cycles++;
        for(int j = 0; j <= matrix[0].size() - 1; j++){            // nord
            int cumulRocks{0};
            for(int k = matrix.size() - 1; k >= 0; k--){
                if(matrix[k][j] == 79 && k > 0){
                    if(k > 0 && matrix[k - 1][j] != 35){
                        cumulRocks++;                            // cumul des pierres qui ne sont pas immédiatement bloquées
                        matrix[k][j] = 46;
                    }
                }
                else if((matrix[k][j] == 35 || k == 0) && cumulRocks > 0){
                    int index{k};
                    while(cumulRocks > 0){                      // répartition de toutes les pierres restantes
                        if(matrix[index][j] == 46){
                            matrix[index][j] = 79;
                            cumulRocks--;
                        }
                        index++;
                    }
                }
            }
        }
        for(int j = 0; j <= matrix.size() - 1; j++){                // ouest
            int cumulRocks{0};
            for(int k = matrix[0].size() - 1; k >= 0; k--){
                if(matrix[j][k] == 79 && k > 0){
                    if(matrix[j][k - 1] != 35){
                        cumulRocks++;
                        matrix[j][k] = 46;
                    }
                }
                else if((matrix[j][k] == 35 || k == 0) && cumulRocks > 0){
                    int index{k};
                    while(cumulRocks > 0){
                        if(matrix[j][index] == 46){
                            matrix[j][index] = 79;
                            cumulRocks--;
                        }
                        index++;
                    }
                }
            }
        }
        for(int j = 0; j <= matrix[0].size() - 1; j++){                 // sud
            int cumulRocks{0};
            for(int k = 0; k <= matrix.size() - 1; k++){
                if(matrix[k][j] == 79 && k < matrix.size() - 1){
                    if(matrix[k + 1][j] != 35){
                        cumulRocks++;
                        matrix[k][j] = 46;
                    }
                }
                else if((matrix[k][j] == 35 || k == matrix.size() - 1) && cumulRocks > 0){
                    int index{k};
                    while(cumulRocks > 0){
                        if(matrix[index][j] == 46){
                            matrix[index][j] = 79;
                            cumulRocks--;
                        }
                        index--;
                    }
                }
            }
        }
        for(int j = 0; j <= matrix.size() - 1; j++){                    // est
            int cumulRocks{0};
            for(int k = 0; k <= matrix[0].size() - 1; k++){
                if(matrix[j][k] == 79 && k < matrix[0].size() - 1){
                    if(matrix[j][k + 1] != 35){
                        cumulRocks++;
                        matrix[j][k] = 46;
                    }
                }
                else if((matrix[j][k] == 35 || k == matrix[0].size() - 1) && cumulRocks > 0){
                    int index{k};
                    while(cumulRocks > 0){
                        if(matrix[j][index] == 46){
                            matrix[j][index] = 79;
                            cumulRocks--;
                        }
                        index--;
                    }
                }
            }
        }
        std::string strRepresentation;
        for(int j = 0; j <= matrix.size() - 1; j++){
            for(int k = 0; k <= matrix[0].size() - 1; k++){
                strRepresentation += matrix[j][k];
            }
        }
        if(std::find(pastStates.begin(), pastStates.end(), strRepresentation) != pastStates.end()){     // si on a déjà vu l'état de la matrice
            repeatState = true;
            for(int k = 0; k <= pastStates.size() - 1; k++){
                if(pastStates[k] == strRepresentation){
                    startLoop = k + 1;
                    break;
                }
            }
        }
        else pastStates.push_back(strRepresentation);
    }
    std::cout << cycles << "\n";
    std::cout << startLoop << "\n";
    int loopLength = cycles - startLoop;      // la taille du cycle
    while(cycles < 1000000000){
        cycles += loopLength;
    }
    if(cycles > 1000000000){
        cycles -= loopLength;
    }
    std::cout << cycles << "\n";
    int lastLoops{1000000000 - cycles};
    while(lastLoops > 0){
        lastLoops--;
        for(int j = 0; j <= matrix[0].size() - 1; j++){            // nord
            int cumulRocks{0};
            for(int k = matrix.size() - 1; k >= 0; k--){
                if(matrix[k][j] == 79 && k > 0){
                    if(k > 0 && matrix[k - 1][j] != 35){
                        cumulRocks++;                            // cumul des pierres qui ne sont pas immédiatement bloquées
                        matrix[k][j] = 46;
                    }
                }
                else if((matrix[k][j] == 35 || k == 0) && cumulRocks > 0){
                    int index{k};
                    while(cumulRocks > 0){                      // répartition de toutes les pierres restantes
                        if(matrix[index][j] == 46){
                            matrix[index][j] = 79;
                            cumulRocks--;
                        }
                        index++;
                    }
                }
            }
        }
        for(int j = 0; j <= matrix.size() - 1; j++){                // ouest
            int cumulRocks{0};
            for(int k = matrix[0].size() - 1; k >= 0; k--){
                if(matrix[j][k] == 79 && k > 0){
                    if(matrix[j][k - 1] != 35){
                        cumulRocks++;
                        matrix[j][k] = 46;
                    }
                }
                else if((matrix[j][k] == 35 || k == 0) && cumulRocks > 0){
                    int index{k};
                    while(cumulRocks > 0){
                        if(matrix[j][index] == 46){
                            matrix[j][index] = 79;
                            cumulRocks--;
                        }
                        index++;
                    }
                }
            }
        }
        for(int j = 0; j <= matrix[0].size() - 1; j++){                 // sud
            int cumulRocks{0};
            for(int k = 0; k <= matrix.size() - 1; k++){
                if(matrix[k][j] == 79 && k < matrix.size() - 1){
                    if(matrix[k + 1][j] != 35){
                        cumulRocks++;
                        matrix[k][j] = 46;
                    }
                }
                else if((matrix[k][j] == 35 || k == matrix.size() - 1) && cumulRocks > 0){
                    int index{k};
                    while(cumulRocks > 0){
                        if(matrix[index][j] == 46){
                            matrix[index][j] = 79;
                            cumulRocks--;
                        }
                        index--;
                    }
                }
            }
        }
        for(int j = 0; j <= matrix.size() - 1; j++){                    // est
            int cumulRocks{0};
            for(int k = 0; k <= matrix[0].size() - 1; k++){
                if(matrix[j][k] == 79 && k < matrix[0].size() - 1){
                    if(matrix[j][k + 1] != 35){
                        cumulRocks++;
                        matrix[j][k] = 46;
                    }
                }
                else if((matrix[j][k] == 35 || k == matrix[0].size() - 1) && cumulRocks > 0){
                    int index{k};
                    while(cumulRocks > 0){
                        if(matrix[j][index] == 46){
                            matrix[j][index] = 79;
                            cumulRocks--;
                        }
                        index--;
                    }
                }
            }
        }
    }
    int res{0};
    int lignWeight{1};
    for(int i = matrix.size() - 1; i >= 0; i--){
        for(int j = 0; j <= matrix[0].size() - 1; j++){
            if(matrix[i][j] == 79){
                res += lignWeight;
            }
        }
        lignWeight++;
    }
    std::cout << res << "\n";
    return 0;
}