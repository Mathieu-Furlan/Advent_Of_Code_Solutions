#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::array<std::array<int, 1000>, 1000> matrix;
    for(int i = 0; i <= 999; i++){
        std::array<int, 1000> temp;
        std::fill(temp.begin(), temp.end(), 0);
        matrix[i] = temp;
    }
    while(getline(file, s)){
        int fromLign{-1};
        int fromCol{-1};
        int toLign{-1};
        int toCol{-1};
        std::string createParameters;
        for(int i =  0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58){
                createParameters += s[i];
            }
            else if(createParameters.length() > 0){
                if(fromCol < 0){
                    fromCol = stoi(createParameters);
                    createParameters.clear();
                }
                else if(fromLign < 0){
                    fromLign = stoi(createParameters);
                    createParameters.clear();
                }
                else if(toCol < 0){
                    toCol = stoi(createParameters);
                    createParameters.clear();
                }
            }
        }
        toLign = stoi(createParameters);
        if(s[6] == 'n'){
            for(int j = fromLign; j <= toLign; j++){
                for(int k = fromCol; k <= toCol; k++){
                    matrix[j][k]++;
                }
            }
        }
        else if(s[6] == 'f'){
            for(int j = fromLign; j <= toLign; j++){
                for(int k = fromCol; k <= toCol; k++){
                    if(matrix[j][k] > 0){
                        matrix[j][k]--;
                    }
                }
            }
        }
        else{
            for(int j = fromLign; j <= toLign; j++){
                for(int k = fromCol; k <= toCol; k++){
                    matrix[j][k] += 2;
                }
            }
        }
    }
    int res{0};
    for(int m = 0; m <= 999; m++){
        for(int n = 0; n <= 999; n++){
            res += matrix[m][n];
        }
    }
    std::cout << res << "\n";
    return res;
}