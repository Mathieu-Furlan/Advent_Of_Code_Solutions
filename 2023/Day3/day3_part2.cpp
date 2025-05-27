/*
  les nombres situés en dessous ou au dessus ont besoin de pointeurs pour éviter de transformer en points (ASCII 46) 
  d'éventuels nombres en diagonale
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
            if(matrix[j][k] == 42){
                std::string temp1;
                std::string temp2;
                bool firstN{false};
                bool secondN{false};
                if(j > 0 && matrix[j - 1][k] >= 48 && matrix[j - 1][k] <= 57){
                    firstN = true;
                    int left = k;
                    while(matrix[j - 1][left] >= 48 && matrix[j - 1][left] <= 57){
                        left--;
                    }
                    left++;
                    int right = k;
                    while(matrix[j - 1][right] >= 48 && matrix[j - 1][right] <= 57){
                        right++;
                    }
                    right--;
                    for(int m = left; m <= right; m++){
                        temp1.push_back(matrix[j - 1][m]);
                        matrix[j - 1][m] = 46;
                    }
                }
                if(k > 0 && matrix[j][k - 1] >= 48 && matrix[j][k - 1] <= 57){
                    if(firstN){
                        secondN = true;
                    }
                    else firstN = true;
                    for(int m = k - 3; m <= k - 1; m++){
                        if(matrix[j][m] >= 48 && matrix[j][m] <= 57){
                            if(secondN){
                                temp2.push_back(matrix[j][m]);
                            }
                            else temp1.push_back(matrix[j][m]);
                            matrix[j][m] = 46;
                        }
                        else if(secondN){
                            temp2.clear();
                        }
                        else temp1.clear();
                    }
                }
                if(j < matrix.size() - 1 && matrix[j + 1][k] >= 48 && matrix[j + 1][k] <= 57){
                    if(firstN && secondN){
                        continue;
                    }
                    if(firstN){
                        secondN = true;
                    }
                    else firstN = true;
                    int left = k;
                    while(matrix[j + 1][left] >= 48 && matrix[j + 1][left] <= 57){
                        left--;
                    }
                    left++;
                    int right = k;
                    while(matrix[j + 1][right] >= 48 && matrix[j + 1][right] <= 57){
                        right++;
                    }
                    right--;
                    for(int m = left; m <= right; m++){
                        if(secondN){
                            temp2.push_back(matrix[j + 1][m]);
                        }
                        else temp1.push_back(matrix[j + 1][m]);
                        matrix[j + 1][m] = 46;
                    }
                }
                if(k < matrix[0].size() - 1 && matrix[j][k + 1] >= 48 && matrix[j][k + 1] <= 57){
                    if(firstN && secondN){
                        continue;
                    }
                    if(firstN){
                        secondN = true;
                    }
                    else firstN = true;
                    for(int m = k + 1; m <= k + 3; m++){
                        if(matrix[j][m] >= 48 && matrix[j][m] <= 57){
                            if(secondN){
                                temp2.push_back(matrix[j][m]);
                            }
                            else temp1.push_back(matrix[j][m]);
                            matrix[j][m] = 46;
                        }
                        else break;
                    }
                }
                if(j > 0 && k > 0 && matrix[j - 1][k - 1] >= 48 && matrix[j - 1][k - 1] <= 57){
                    if(firstN && secondN){
                        continue;
                    }
                    if(firstN){
                        secondN = true;
                    }
                    else firstN = true;
                    for(int m = k - 3; m <= k - 1; m++){
                        if(matrix[j - 1][m] >= 48 && matrix[j - 1][m] <= 57){
                            if(secondN){
                                temp2.push_back(matrix[j - 1][m]);
                            }
                            else temp1.push_back(matrix[j - 1][m]);
                            matrix[j - 1][m] = 46;
                        }
                        else if(secondN){
                            temp2.clear();
                        }
                        else temp1.clear();
                    }
                }
                if(j < matrix.size() - 1 && k > 0 && matrix[j + 1][k - 1] >= 48 && matrix[j + 1][k - 1] <= 57){
                    if(firstN && secondN){
                        continue;
                    }
                    if(firstN){
                        secondN = true;
                    }
                    else firstN = true;
                    for(int m = k - 3; m <= k - 1; m++){
                        if(matrix[j + 1][m] >= 48 && matrix[j + 1][m] <= 57){
                            if(secondN){
                                temp2.push_back(matrix[j + 1][m]);
                            }
                            else temp1.push_back(matrix[j + 1][m]);
                            matrix[j + 1][m] = 46;
                        }
                        else if(secondN){
                            temp2.clear();
                        }
                        else temp1.clear();
                    }
                }
                if(j > 0 && k < matrix[0].size() - 1 && matrix[j - 1][k + 1] >= 48 && matrix[j - 1][k + 1] <= 57){
                    if(firstN && secondN){
                        continue;
                    }
                    if(firstN){
                        secondN = true;
                    }
                    else firstN = true;
                    for(int m = k + 1; m <= k + 3; m++){
                        if(matrix[j - 1][m] >= 48 && matrix[j - 1][m] <= 57){
                            if(secondN){
                                temp2.push_back(matrix[j - 1][m]);
                            }
                            else temp1.push_back(matrix[j - 1][m]);
                            matrix[j - 1][m] = 46;
                        }
                        else break;
                    }
                }
                if(j < matrix.size() - 1 && k < matrix[0].size() - 1 && matrix[j + 1][k + 1] >= 48 && matrix[j + 1][k + 1] <= 57){
                    if(firstN && secondN){
                        continue;
                    }
                    if(firstN){
                        secondN = true;
                    }
                    else firstN = true;
                    for(int m = k + 1; m <= k + 3; m++){
                        if(matrix[j + 1][m] >= 48 && matrix[j + 1][m] <= 57){
                            if(secondN){
                                temp2.push_back(matrix[j + 1][m]);
                            }
                            else temp1.push_back(matrix[j + 1][m]);
                            matrix[j + 1][m] = 46;
                        }
                        else break;
                    }
                }
                std::cout << "temp1 " << temp1 << "\n";
                std::cout << "temp2 " << temp2 << "\n";
                if(firstN && secondN){
                    int nbre1{stoi(temp1)};
                    int nbre2{stoi(temp2)};
                    res += nbre1 * nbre2;
                }
            }
        }
    }
    std::cout << res << "\n";
    return res;
}