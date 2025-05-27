#include <fstream>
#include <string>
#include <iostream>
#include <vector>

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
    for(int j = 0; j <= matrix[0].size() - 1; j++){
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
        std::cout << "rocks remaining " << cumulRocks << "\n";
    }
    int res{0};                                               // calcul des poids
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
    return res;
}