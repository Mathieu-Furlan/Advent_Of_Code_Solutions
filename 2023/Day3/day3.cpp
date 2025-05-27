/*
  && a une priorité plus importante que ||, il faut des parenthèses pour éviter la segmentation fault;
*/
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
    int res{0};
    for(int j = 0; j <= matrix.size() - 1; j++){
        for(int k = 0; k <= matrix[0].size() - 1; k++){
            if(matrix[j][k] >= 48 && matrix[j][k] <= 57){
                bool contiguous{false};
                std::string temp;
                while(k <= matrix[0].size() - 1 && matrix[j][k] >= 48 && matrix[j][k] <= 57){
                    temp.push_back(matrix[j][k]);
                    if(j > 0 && matrix[j - 1][k] != 46 && (matrix[j - 1][k] < 48 || matrix[j - 1][k] > 57)){
                        contiguous = true;
                    }
                    if(k > 0 && matrix[j][k - 1] != 46 && (matrix[j][k - 1] < 48 || matrix[j][k - 1] > 57)){
                        contiguous = true;
                    }
                    if(j < matrix.size() - 1 && matrix[j + 1][k] != 46 && (matrix[j + 1][k] < 48 || matrix[j + 1][k] > 57)){
                        contiguous = true;
                    }
                    if(k < matrix[0].size() - 1 && matrix[j][k + 1] != 46 && (matrix[j][k + 1] < 48 || matrix[j][k + 1] > 57)){
                        contiguous = true;
                    }
                    if(j > 0 && k > 0 && matrix[j - 1][k - 1] != 46 && (matrix[j - 1][k - 1] < 48 || matrix[j - 1][k - 1] > 57)){
                        contiguous = true;
                    }
                    if(j < matrix.size() - 1 && k > 0 && matrix[j + 1][k - 1] != 46 && (matrix[j + 1][k - 1] < 48 || matrix[j + 1][k - 1] > 57)){
                        contiguous = true;
                    }
                    if(j > 0 && k < matrix[0].size() - 1 && matrix[j - 1][k + 1] != 46 && (matrix[j - 1][k + 1] < 48 || matrix[j - 1][k + 1] > 57)){
                        contiguous = true;
                    }
                    if(j < matrix.size() - 1 && k < matrix[0].size() - 1 && matrix[j + 1][k + 1] != 46 && (matrix[j + 1][k + 1] < 48 || matrix[j + 1][k + 1] > 57)){
                        contiguous = true;
                    }
                    k++;
                }
                if(contiguous){
                    int nbre{stoi(temp)};
                    res += nbre;
                }
            }
        }
    }
    std::cout << res << "\n";
    return res;
}