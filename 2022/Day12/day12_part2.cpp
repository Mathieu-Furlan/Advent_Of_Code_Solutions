#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <limits>

int findPath(int row, int col, int endLign, int endCol, std::vector<std::vector<char>>& matrix, std::vector<std::vector<char>> duplicate){
    int res{0};
    std::queue<std::array<int, 2>> elems;
    elems.push({row, col});
    duplicate[row][col] = 35;
    while(elems.size() > 0){
        unsigned long level{elems.size()};
        while(level > 0){
            int currLign{elems.front()[0]};
            int currCol{elems.front()[1]};
            if(currLign == endLign && currCol == endCol){
                return res;
            }
            elems.pop();
            if(currLign > 0 && duplicate[currLign - 1][currCol] != 35 && matrix[currLign][currCol] + 1 >= matrix[currLign - 1][currCol]){
                duplicate[currLign - 1][currCol] = 35;
                elems.push({currLign - 1, currCol});
            }
            if(currLign < matrix.size() - 1 && duplicate[currLign + 1][currCol] != 35 && matrix[currLign][currCol] + 1 >= matrix[currLign + 1][currCol]){
                duplicate[currLign + 1][currCol] = 35;
                elems.push({currLign + 1, currCol});
            }
            if(currCol < matrix[0].size() - 1 && duplicate[currLign][currCol + 1] != 35 && matrix[currLign][currCol] + 1 >= matrix[currLign][currCol + 1]){
                duplicate[currLign][currCol + 1] = 35;
                elems.push({currLign, currCol + 1});
            }
            if(currCol > 0 && duplicate[currLign][currCol - 1] != 35 && matrix[currLign][currCol] + 1 >= matrix[currLign][currCol - 1]){
                duplicate[currLign][currCol - 1] = 35;
                elems.push({currLign, currCol - 1});
            }
            level--;
        }
        res++;
    }
    return 0;
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::vector<char>> matrix;
    std::vector<std::vector<char>> duplicate;
    int endLign{0};
    int endColumn{0};
    int lign{0};
    while(getline(file, s)){
        std::vector<char> temp;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == 'S'){
                temp.push_back('a');
            }
            else if(s[i] == 'E'){
                endColumn = i;
                endLign = lign;
                temp.push_back('z');
            }
            else temp.push_back(s[i]);
        }
        matrix.push_back(temp);
        duplicate.push_back(temp);
        lign++;
    }
    int fewestSteps{std::numeric_limits<int>::max()};
    for(int k = 0; k <= matrix.size() - 1; k++){
        for(int m = 0; m <= matrix[0].size() - 1; m++){
            if(matrix[k][m] == 'a'){
                int res{findPath(k, m, endLign, endColumn, matrix, duplicate)};
                if(res > 0 && res < fewestSteps){
                    fewestSteps = res;
                }
            }
        }
    }
    std::cout << fewestSteps << "\n";
    return 0;
}