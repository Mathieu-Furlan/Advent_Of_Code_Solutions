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
                    if(i > 0){
                        for(int k = i - 1; k >= 0; k--){
                            if(matrix[k][j] == '#'){
                                nearOccupied = true;
                                break;
                            }
                            else if(matrix[k][j] == 'L'){
                                break;
                            }
                        }
                    }
                    if(!nearOccupied && i > 0 && j > 0){
                        int row{i - 1};
                        int col{j - 1};
                        while(row >= 0 && col >= 0){
                            if(matrix[row][col] == '#'){
                                nearOccupied = true;
                                break;
                            }
                            else if(matrix[row][col] == 'L'){
                                break;
                            }
                            row--;
                            col--;
                        }
                    }
                    if(!nearOccupied && i > 0 && j < matrix[0].size() - 1){
                        int row{i - 1};
                        int col{j + 1};
                        while(row >= 0 && col < matrix[0].size()){
                            if(matrix[row][col] == '#'){
                                nearOccupied = true;
                                break;
                            }
                            else if(matrix[row][col] == 'L'){
                                break;
                            }
                            row--;
                            col++;
                        }
                    }
                    if(!nearOccupied && j > 0){
                        for(int k = j - 1; k >= 0; k--){
                            if(matrix[i][k] == '#'){
                                nearOccupied = true;
                                break;
                            }
                            else if(matrix[i][k] == 'L'){
                                break;
                            }
                        }
                    }
                    if(!nearOccupied && j < matrix[0].size() - 1){
                        for(int k = j + 1; k < matrix[0].size(); k++){
                            if(matrix[i][k] == '#'){
                                nearOccupied = true;
                                break;
                            }
                            else if(matrix[i][k] == 'L'){
                                break;
                            }
                        }
                    }
                    if(!nearOccupied && i < matrix.size() - 1 && j < matrix[0].size() - 1){
                        int row{i + 1};
                        int col{j + 1};
                        while(row < matrix.size() && col < matrix[0].size()){
                            if(matrix[row][col] == '#'){
                                nearOccupied = true;
                                break;
                            }
                            else if(matrix[row][col] == 'L'){
                                break;
                            }
                            row++;
                            col++;
                        }
                    }
                    if(!nearOccupied && i < matrix.size() - 1 && j > 0){
                        int row{i + 1};
                        int col{j - 1};
                        while(row < matrix.size() && col >= 0){
                            if(matrix[row][col] == '#'){
                                nearOccupied = true;
                                break;
                            }
                            else if(matrix[row][col] == 'L'){
                                break;
                            }
                            row++;
                            col--;
                        }
                    }
                    if(!nearOccupied && i < matrix.size() - 1){
                        for(int k = i + 1; k < matrix.size(); k++){
                            if(matrix[k][j] == '#'){
                                nearOccupied = true;
                                break;
                            }
                            else if(matrix[k][j] == 'L'){
                                break;
                            }
                        }
                    }
                    if(!nearOccupied){
                        emptyToOccupied.push_back({i, j});
                    }
                }
                else if(matrix[i][j] == '#'){
                    int closeOcccupied{0};
                    if(i > 0){
                        for(int k = i - 1; k >= 0; k--){
                            if(matrix[k][j] == '#'){
                                closeOcccupied++;
                                break;
                            }
                            else if(matrix[k][j] == 'L'){
                                break;
                            }
                        }
                    }
                    if(i > 0 && j > 0){
                        int row{i - 1};
                        int col{j - 1};
                        while(row >= 0 && col >= 0){
                            if(matrix[row][col] == '#'){
                                closeOcccupied++;
                                break;
                            }
                            else if(matrix[row][col] == 'L'){
                                break;
                            }
                            row--;
                            col--;
                        }
                    }
                    if(i > 0 && j < matrix[0].size() - 1){
                        int row{i - 1};
                        int col{j + 1};
                        while(row >= 0 && col < matrix[0].size()){
                            if(matrix[row][col] == '#'){
                                closeOcccupied++;
                                break;
                            }
                            else if(matrix[row][col] == 'L'){
                                break;
                            }
                            row--;
                            col++;
                        }
                    }
                    if(j > 0){
                        for(int k = j - 1; k >= 0; k--){
                            if(matrix[i][k] == '#'){
                                closeOcccupied++;
                                break;
                            }
                            else if(matrix[i][k] == 'L'){
                                break;
                            }
                        }
                    }
                    if(j < matrix[0].size() - 1){
                        for(int k = j + 1; k < matrix[0].size(); k++){
                            if(matrix[i][k] == '#'){
                                closeOcccupied++;
                                break;
                            }

                            else if(matrix[i][k] == 'L'){
                                break;
                            }
                        }
                    }
                    if(i < matrix.size() - 1 && j < matrix[0].size() - 1){
                        int row{i + 1};
                        int col{j + 1};
                        while(row < matrix.size() && col < matrix[0].size()){
                            if(matrix[row][col] == '#'){
                                closeOcccupied++;
                                break;
                            }
                            else if(matrix[row][col] == 'L'){
                                break;
                            }
                            row++;
                            col++;
                        }
                    }
                    if(i < matrix.size() - 1 && j > 0){
                        int row{i + 1};
                        int col{j - 1};
                        while(row < matrix.size() && col >= 0){
                            if(matrix[row][col] == '#'){
                                closeOcccupied++;
                                break;
                            }
                            else if(matrix[row][col] == 'L'){
                                break;
                            }
                            row++;
                            col--;
                        }
                    }
                    if(i < matrix.size() - 1){
                        for(int k = i + 1; k < matrix.size(); k++){
                            if(matrix[k][j] == '#'){
                                closeOcccupied++;
                                break;
                            }
                            else if(matrix[k][j] == 'L'){
                                break;
                            }
                        }
                    }
                    if(closeOcccupied >= 5){
                        occupiedToEmpty.push_back({i, j});
                    }
                }
            }
        }
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