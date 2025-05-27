#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::vector<char>> matrix;
    int res{0};
    int matrixNumber{0};
    while(getline(file, s) || file.peek() == EOF){         // la boucle est exécutée une dernière fois à la fin du fichier pour la dernière matrice
        if(s[0] == 35 || s[0] == 46){
            std::vector<char> temp;
            for(int i = 0; i <= s.length() - 1; i++){
                temp.push_back(s[i]);
            }
            matrix.push_back(temp);
        }
        else{
            for(int j = 1; j <= matrix.size() - 1; j++){        // vérifie si reflexion horizontale
                bool symetric{true};
                bool smudge{false};
                int index{j};
                int gap{1};
                while(symetric){
                    for(int k = 0; k <= matrix[0].size() - 1; k++){
                        if(index == matrix.size() || gap > matrix.size() / 2 || j - gap < 0 || matrix[index][k] != matrix[j - gap][k]){  // vérifier que l'écart (gap) ne dépasse pas la moitié de la matrice et ne soit pas plus grand que j et aussi qu'index ne dépasse pas la taille de la matrice
                            if(smudge){                         // vérifie la présence d'une seule différence
                                symetric = false;
                                break;
                            }
                            else smudge = true;
                        }
                    }
                    index++;
                    gap++;
                    if(symetric && smudge && (index == matrix.size() || j - gap < 0)){
                        res += j * 100;
                        std::cout << "res hori " << res << "\n";
                    }
                }
            }
            for(int j = 1; j <= matrix[0].size() - 1; j++){       // vérifie si reflexion verticale
                bool symetric{true};
                bool smudge{false};
                int index{j};
                int gap{1};
                while(symetric){
                    for(int k = 0; k <= matrix.size() - 1; k++){
                        if(matrix[k][index] != matrix[k][j - gap]){
                            if(smudge){
                                symetric = false;
                                break;
                            }
                            else smudge = true;
                        }
                    }
                    index++;
                    gap++;
                    if(symetric && smudge && (index == matrix[0].size() || j - gap < 0)){
                        res += j;
                        std::cout << "res vert " << res << "\n";
                    }
                }
            }
            matrix.clear();
            matrixNumber++;
            std::cout << "next matrix " << matrixNumber <<"\n";
        }
        if(file.eof()){
            break;
        }
    }
    std::cout << res << "\n";
    return res;
}