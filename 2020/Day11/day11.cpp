#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::vector<char>> matrix;
    while(getline(file, s)){
        std::vector<char> createRow;
        for(int i = 0; i <= s.length() - 1; i++){
            createRow.push_back(s[i]);
        }
        matrix.push_back(createRow);
    }
    bool unchanged{false};
    while(!unchanged){
        std::vector<std::array<int, 2>> emptyToOccupied;
        std::vector<std::array<int, 2>> occupiedToEmpty;
        for(int i = 0; i <= matrix.size() - 1; i++){
            for(int j = 0; j <= matrix[0].size() - 1; j++){
                if(matrix[i][j] == 'L'){
                    bool nearOccupied{false};
                    if(i > 0 && matrix[i - 1][j] == '#'){
                        nearOccupied = true;
                    }
                    else if(i > 0 && j > 0 && matrix[i - 1][j - 1] == '#'){
                        nearOccupied = true;
                    }
                    else if(i > 0 && j < matrix[0].size() - 1 && matrix[i - 1][j + 1] == '#'){
                        nearOccupied = true;
                    }
                    else if(j > 0 && matrix[i][j - 1] == '#'){
                        nearOccupied = true;
                    }
                    else if(j < matrix[0].size() - 1 && matrix[i][j + 1] == '#'){
                        nearOccupied = true;
                    }
                    else if(i < matrix.size() - 1 && j < matrix[0].size() - 1 && matrix[i + 1][j + 1] == '#'){
                        nearOccupied = true;
                    }
                    else if(i < matrix.size() - 1 && j > 0 && matrix[i + 1][j - 1] == '#'){
                        nearOccupied = true;
                    }
                    else if(i < matrix.size() - 1 && matrix[i + 1][j] == '#'){
                        nearOccupied = true;
                    }
                    if(!nearOccupied){
                        emptyToOccupied.push_back({i, j});
                    }
                }
                else if(matrix[i][j] == '#'){
                    int closeOcccupied{0};
                    if(i > 0 && matrix[i - 1][j] == '#'){
                        closeOcccupied++;
                    }
                    if(i > 0 && j > 0 && matrix[i - 1][j - 1] == '#'){
                        closeOcccupied++;
                    }
                    if(i > 0 && j < matrix[0].size() - 1 && matrix[i - 1][j + 1] == '#'){
                        closeOcccupied++;
                    }
                    if(j > 0 && matrix[i][j - 1] == '#'){
                        closeOcccupied++;
                    }
                    if(j < matrix[0].size() - 1 && matrix[i][j + 1] == '#'){
                        closeOcccupied++;
                    }
                    if(i < matrix.size() - 1 && j < matrix[0].size() - 1 && matrix[i + 1][j + 1] == '#'){
                        closeOcccupied++;
                    }
                    if(i < matrix.size() - 1 && j > 0 && matrix[i + 1][j - 1] == '#'){
                        closeOcccupied++;
                    }
                    if(i < matrix.size() - 1 && matrix[i + 1][j] == '#'){
                        closeOcccupied++;
                    }
                    if(closeOcccupied >= 4){
                        occupiedToEmpty.push_back({i, j});
                    }
                }
            }
        }
        for(int i = 0; i <= matrix.size() - 1; i++){
            for(int j = 0; j <= matrix[0].size() - 1; j++){
                std::cout << matrix[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        if(emptyToOccupied.size() == 0 && occupiedToEmpty.size() == 0){
            unchanged = true;
        }
        for(auto& toChange : emptyToOccupied){
            matrix[toChange[0]][toChange[1]] = '#';
        }
        for(auto& toChange : occupiedToEmpty){
            matrix[toChange[0]][toChange[1]] = 'L';
        }
    }
    int res{0};
    for(int i = 0; i <= matrix.size() - 1; i++){
        for(int j = 0; j <= matrix[0].size() - 1; j++){
            std::cout << matrix[i][j];
            if(matrix[i][j] == '#'){
                res++;
            }
        }
        std::cout << "\n";
    }
    std::cout << res << "\n";
    return 0;
}