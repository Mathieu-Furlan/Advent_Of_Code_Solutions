#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>

int res{0};
std::vector<std::vector<char>> matrix;

void trackPath(int pathLength, std::array<int, 2> coordinates){
    int currLign{coordinates[0]};
    int currCol{coordinates[1]};
    matrix[currLign][currCol] = '#';
    if(currLign == matrix.size() - 1){
        if(pathLength > res){
            res = pathLength;
        }
        return;
    }
    std::vector<std::array<int, 2>> nextSteps;
    if(currLign < matrix.size() - 1 && matrix[currLign + 1][currCol] == '.'){
        trackPath(pathLength + 1, {currLign + 1, currCol});
    }
    if(currLign > 0 && matrix[currLign - 1][currCol] == '.'){
        trackPath(pathLength + 1, {currLign - 1, currCol});
    }
    if(currCol <= matrix[0].size() - 1 && matrix[currLign][currCol + 1] == '.'){
        trackPath(pathLength + 1, {currLign, currCol + 1});
    }
    if(currCol > 0 && matrix[currLign][currCol - 1] == '.'){
        trackPath(pathLength + 1, {currLign, currCol - 1});
    }
    matrix[currLign][currCol] = '.';
    return;
}

int main(){
    std::ifstream file("inputtest");
    std::string s;
    int startLign{0};
    int startColumn{0};
    getline(file, s);
    std::vector<char> tempInit;
    for(int i = 0; i <= s.length() - 1; i++){
        tempInit.push_back(s[i]);
        if(s[i] == '.'){
            startColumn = i;
        }
    }
    matrix.push_back(tempInit);
    while(getline(file, s)){
        std::vector<char> temp;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == 'v' || s[i] == '<' || s[i] == '>'){
                temp.push_back('.');
            }
            else temp.push_back(s[i]);
        }
        matrix.push_back(temp);
    }
    trackPath(0, {startLign, startColumn});
    std::cout << res << "\n";
    return res;
}