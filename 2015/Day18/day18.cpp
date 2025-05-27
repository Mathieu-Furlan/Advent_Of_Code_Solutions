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
    std::vector<std::vector<char>> duplicate;
    duplicate = matrix;
    int stepsTurn{100};
    while(stepsTurn > 0){
        for(int i = 0; i <= matrix.size() - 1; i++){
            for(int j = 0; j <= matrix[0].size() - 1; j++){
                int lightsOn{0};
                if(j > 0){
                    if(matrix[i][j - 1] == '#'){
                        lightsOn++;
                    }
                    if(i > 0 && matrix[i - 1][j - 1] == '#'){
                        lightsOn++;
                    }
                    if(i < matrix.size() - 1 && matrix[i + 1][j - 1] == '#'){
                        lightsOn++;
                    }
                }
                if(j < matrix[0].size() - 1){
                    if(matrix[i][j + 1] == '#'){
                        lightsOn++;
                    }
                    if(i > 0 && matrix[i - 1][j + 1] == '#'){
                        lightsOn++;
                    }
                    if(i < matrix.size() - 1 && matrix[i + 1][j + 1] == '#'){
                        lightsOn++;
                    }
                }
                if(i > 0 && matrix[i - 1][j] == '#'){
                    lightsOn++;
                }
                if(i < matrix.size() - 1 && matrix[i + 1][j] == '#'){
                    lightsOn++;
                }
                if(lightsOn == 3 && matrix[i][j] == '.'){
                    duplicate[i][j] = '#';
                }
                else if(lightsOn > 3 || lightsOn < 2 && matrix[i][j] == '#'){
                    duplicate[i][j] = '.';
                }
            }
        }
        stepsTurn--;
        matrix = duplicate;
    }
    int res{0};
    for(int i = 0; i <= matrix.size() - 1; i++){
        for(int j = 0; j <= matrix[0].size() - 1; j++){
            if(matrix[i][j] == '#'){
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}