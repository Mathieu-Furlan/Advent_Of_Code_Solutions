#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::vector<std::vector<int>> matrix;
    while(getline(file, s)){
        std::vector<int> temp;
        for(int i = 0; i <= s.length() - 1; i++){
            temp.push_back(s[i]);
        }
        matrix.push_back(temp);
    }
    for(int j =1; j <= matrix.size() - 2; j++){
        for(int k = 1; k <= matrix[0].size() - 2; k++){
            bool visibility{false};
            int lign{j - 1};
            int col{k};
            while(lign >= 0){
                if(matrix[lign][col] >= matrix[j][k]){
                    break;
                }
                else if(lign == 0 && matrix[lign][col] <= matrix[j][k]){
                    visibility = true;
                }
                lign--;
            }
            lign = j + 1;
            if(!visibility){
                while(lign <= matrix.size() - 1){
                    if(matrix[lign][col] >= matrix[j][k]){
                        break;
                    }
                    else if(lign == matrix.size() - 1 && matrix[lign][col] <= matrix[j][k]){
                        visibility = true;
                    }
                    lign++;
                }
            }
            lign = j;
            col = k - 1;
            if(!visibility){
                while(col >= 0){
                    if(matrix[lign][col] >= matrix[j][k]){
                        break;
                    }
                    else if(col == 0 && matrix[lign][col] <= matrix[j][k]){
                        visibility = true;
                    }
                    col--;
                }
            }
            col = k + 1;
            if(!visibility){
                while(col <= matrix[0].size() - 1){
                    if(matrix[lign][col] >= matrix[j][k]){
                        break;
                    }
                    else if(col == matrix[0].size() - 1 && matrix[lign][col] <= matrix[j][k]){
                        visibility = true;
                    }
                    col++;
                }
            }
            if(visibility){
                res++;
            }
        }
    }
    res += matrix.size() * 2;
    res += (matrix[0].size() - 2) * 2;
    std::cout << res << "\n";
    return res;
}