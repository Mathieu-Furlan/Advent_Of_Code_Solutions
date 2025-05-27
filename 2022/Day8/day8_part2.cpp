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
            int viewNorth{0};
            int viewSouth{0};
            int viewEast{0};
            int viewWest{0};
            int lign{j - 1};
            int col{k};
            while(lign >= 0){
                if(matrix[lign][col] >= matrix[j][k]){
                    viewNorth++;
                    break;
                }
                lign--;
                viewNorth++;
            }
            lign = j + 1;
            while(lign <= matrix.size() - 1){
                if(matrix[lign][col] >= matrix[j][k]){
                    viewSouth++;
                    break;
                }
                lign++;
                viewSouth++;
            }
            lign = j;
            col = k - 1;
            while(col >= 0){
                if(matrix[lign][col] >= matrix[j][k]){
                    viewWest++;
                    break;
                }
                col--;
                viewWest++;
            }
            col = k + 1;
            while(col <= matrix[0].size() - 1){
                if(matrix[lign][col] >= matrix[j][k]){
                    viewEast++;
                    break;
                }
                col++;
                viewEast++;
            }
            int view{viewNorth * viewSouth * viewEast * viewWest};
            if(view > res){
                res = view;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}