#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    const int COLUMNS{4000000};
    std::vector<std::array<int, 3>> matrix;
    while(getline(file, s)){
        std::string valueBuilder;
        int valSelector{0};
        int x1;
        int y1;
        int x2;
        int y2;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == '-' || s[i] > 47 && s[i] < 58){
                valueBuilder += s[i];
                int index{i + 1};
                while(s[index] > 47 && s[index] < 58){
                    valueBuilder += s[index];
                    index++;
                    i++;
                }
                if(valSelector == 0){
                    x1 = std::stoi(valueBuilder);
                    valSelector++;
                    valueBuilder.clear();
                }
                else if(valSelector == 1){
                    y1 = std::stoi(valueBuilder);
                    valSelector++;
                    valueBuilder.clear();
                }
                else if(valSelector == 2){
                    x2 = std::stoi(valueBuilder);
                    valSelector++;
                    valueBuilder.clear();
                }
                else if(valSelector == 3){
                    y2 = std::stoi(valueBuilder);
                    valSelector++;
                    valueBuilder.clear();
                }
            }
        }
        int distance{std::abs(x2 - x1) + std::abs(y2 - y1)};      // la distance entre le beacon et le sensor
        int surfaceIncreaseLeft{0};
        for(int i = distance; i >= 0; i--){          // la matrice contient le numéro de la colonne et l'intervalle correspondant à la surface couverte dans un tableau à trois entrées
            if(x1 - i >= 0){                        // colonnes entre 0 et 4 millions
                matrix.push_back({x1 - i, y1 - surfaceIncreaseLeft < 0 ? 0 : y1 - surfaceIncreaseLeft, y1 + surfaceIncreaseLeft > COLUMNS ? COLUMNS : y1 + surfaceIncreaseLeft});
            }
            surfaceIncreaseLeft++;
        }
        int surfaceIncreaseRight{0};
        for(int i = distance; i > 0; i--){
            if(x1 + i <= COLUMNS){                // les lignes ne doivent pas être inférieures à 0 ni supérieures à 4000000
                matrix.push_back({x1 + i, y1 - surfaceIncreaseRight < 0 ? 0 : y1 - surfaceIncreaseRight, y1 + surfaceIncreaseRight > COLUMNS ? COLUMNS : y1 + surfaceIncreaseRight});
            }
            surfaceIncreaseRight++;
        }
    }
    std::sort(matrix.begin(), matrix.end(), [](const std::array<int, 3>& a, const std::array<int, 3>& b){ // on trie les intervalles par colonnes et par lignes
        if(a[0] < b[0]){
            return true;
        }
        else if(a[0] > b[0]){
            return false;
        }
        else if(a[1] < b[1]){
            return true;
        }
        else if(a[1] > b[1]){
            return false;
        }
        else if(a[2] < b[2]){
            return true;
        }
        else if(a[2] > b[2]){
            return false;
        }
        return true;
    });
    for(int m = 1; m <= matrix.size() - 1; m++){
        if(matrix[m][0] == matrix[m - 1][0] && matrix[m][2] < matrix[m - 1][2]){  // si un intervalle est contenu dans le précédent on garde la plus grande valeur de ligne
            matrix[m][2] = matrix[m - 1][2];
        }
        if(matrix[m][0] == matrix[m - 1][0] && matrix[m][1] > matrix[m - 1][2] + 1){  // si il y a un écart entre deux intervalles
            std::cout << "col " << matrix[m][0] << "\n";
            std::cout << "row " << matrix[m][1] - 1 << "\n";
            long long res{matrix[m][0]};
            res *= 4000000;
            res += matrix[m][1] - 1;
            std::cout << res << "\n";
        }
    }
    return 0;
}