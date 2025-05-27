#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::vector<char>> matrix;
    std::vector<std::vector<std::array<char, 4>>> directions;
    std::vector<std::vector<char>> energized;
    while(getline(file, s)){
        std::vector<char> temp;
        std::vector<std::array<char, 4>> dir;
        std::array<char, 4> tempDir{{48, 48, 48, 48}};
        for(int i = 0; i <= s.length() - 1; i++){
            temp.push_back(s[i]);
            dir.push_back(tempDir);
        }
        matrix.push_back(temp);
        energized.push_back(temp);
        directions.push_back(dir);

    }
    std::stack<std::array<int, 3>> stackPath;
    stackPath.push({0, 0, 114});                 // 108 pour l (left), 114 r (right), 116 t (top), 98 b (bottom);
    while(!stackPath.empty()){
        int currLign{stackPath.top()[0]};
        int currCol{stackPath.top()[1]};
        int prevDirection{stackPath.top()[2]};  // direction précédente pour ne pas rester bloqué dans une boucle
        stackPath.pop();
        std::cout << "currLign " << currLign << "\n";
        std::cout << "currCol " << currCol << "\n";
        energized[currLign][currCol] = 35;
        if(matrix[currLign][currCol] == 46){                  // si .
            if(prevDirection == 114 && currCol < matrix[0].size() - 1 && directions[currLign][currCol + 1][1] == 48){
                directions[currLign][currCol + 1][1] = 114;
                stackPath.push({currLign, currCol + 1, 114});
            }
            else if(prevDirection == 108 && currCol > 0 && directions[currLign][currCol - 1][0] == 48){
                directions[currLign][currCol - 1][0] = 108;
                stackPath.push({currLign, currCol - 1, 108});
            }
            else if(prevDirection == 116 && currLign > 0 && directions[currLign - 1][currCol][2] == 48){
                directions[currLign - 1][currCol][2] = 116;
                stackPath.push({currLign - 1, currCol, 116});
            }
            else if(prevDirection == 98 && currLign < matrix.size() - 1 && directions[currLign + 1][currCol][3] == 48){
                directions[currLign + 1][currCol][3] = 98;
                stackPath.push({currLign + 1, currCol, 98});
            }
        }
        else if(matrix[currLign][currCol] == 47){              // si /
            if(prevDirection == 114 && currLign > 0 && directions[currLign - 1][currCol][2] == 48){
                directions[currLign - 1][currCol][2] = 116;
                stackPath.push({currLign - 1, currCol, 116});
            }
            else if(prevDirection == 108 && currLign < matrix.size() - 1 && directions[currLign + 1][currCol][3] == 48){
                directions[currLign + 1][currCol][3] = 98;
                stackPath.push({currLign + 1, currCol, 98});
            }
            else if(prevDirection == 116 && currCol > 0 && directions[currLign][currCol + 1][1] == 48){
                directions[currLign][currCol + 1][1] = 114;
                stackPath.push({currLign, currCol + 1, 114});
            }
            else if(prevDirection == 98 && currCol < matrix[0].size() - 1 && directions[currLign][currCol - 1][0] == 48){
                directions[currLign][currCol - 1][0] = 108;
                stackPath.push({currLign, currCol - 1, 108});
            }
        }
        else if(matrix[currLign][currCol] == 92){              // si '\'
            if(prevDirection == 114 && currLign < matrix.size() - 1 && directions[currLign + 1][currCol][3] == 48){
                directions[currLign + 1][currCol][3] = 98;
                stackPath.push({currLign + 1, currCol, 98});
            }
            else if(prevDirection == 108 && currLign > 0 && directions[currLign - 1][currCol][2] == 48){
                directions[currLign - 1][currCol][2] = 116;
                stackPath.push({currLign - 1, currCol, 116});
            }
            else if(prevDirection == 116 && currCol > 0 && directions[currLign][currCol - 1][0] == 48){
                directions[currLign][currCol - 1][0] = 108;
                stackPath.push({currLign, currCol - 1, 108});
            }
            else if(prevDirection == 98 && currCol < matrix[0].size() - 1 && directions[currLign][currCol + 1][1] == 48){
                directions[currLign][currCol + 1][1] = 114;
                stackPath.push({currLign, currCol + 1, 114});
            }
        }
        else if(matrix[currLign][currCol] == 124){              // si |
            if(prevDirection == 116 && currLign > 0 && directions[currLign - 1][currCol][2] == 48){
                directions[currLign - 1][currCol][2] = 116;
                stackPath.push({currLign - 1, currCol, 116});
            }
            else if(prevDirection == 98 && currLign < matrix.size() - 1 && directions[currLign + 1][currCol][3] == 48){
                directions[currLign + 1][currCol][3] = 98;
                stackPath.push({currLign + 1, currCol, 98});
            }
            else if(prevDirection == 108){
                if(currLign < matrix.size() - 1 && directions[currLign + 1][currCol][3] == 48){
                    directions[currLign + 1][currCol][3] = 98;
                    stackPath.push({currLign + 1, currCol, 98});
                }
                if(currLign > 0 && directions[currLign - 1][currCol][2] == 48){
                    directions[currLign - 1][currCol][2] = 116;
                    stackPath.push({currLign - 1, currCol, 116});
                }
            }
            else if(prevDirection == 114){
                if(currLign < matrix.size() - 1 && directions[currLign + 1][currCol][3] == 48){
                    directions[currLign + 1][currCol][3] = 98;
                    stackPath.push({currLign + 1, currCol, 98});
                }
                if(currLign > 0 && directions[currLign - 1][currCol][2] == 48){
                    directions[currLign - 1][currCol][2] = 116;
                    stackPath.push({currLign - 1, currCol, 116});
                }
            }
        }
        else if(matrix[currLign][currCol] == 45){              // si -
            if(prevDirection == 108 && currCol > 0 && directions[currLign][currCol - 1][0] == 48){
                directions[currLign][currCol - 1][0] = 108;
                stackPath.push({currLign, currCol - 1, 108});
            }
            else if(prevDirection == 114 && currCol < matrix[0].size() - 1 && directions[currLign][currCol + 1][1] == 48){
                directions[currLign][currCol + 1][1] = 114;
                stackPath.push({currLign, currCol + 1, 114});
            }
            else if(prevDirection == 116){
                if(currCol < matrix[0].size() - 1 && directions[currLign][currCol + 1][1] == 48){
                    directions[currLign][currCol + 1][1] = 114;
                    stackPath.push({currLign, currCol + 1, 114});
                }
                if(currCol > 0 && directions[currLign][currCol - 1][0] == 48){
                    directions[currLign][currCol - 1][0] = 108;
                    stackPath.push({currLign, currCol - 1, 108});
                }
            }
            else if(prevDirection == 98){
                if(currCol < matrix[0].size() - 1 && directions[currLign][currCol + 1][1] == 48){
                    directions[currLign][currCol + 1][1] = 114;
                    stackPath.push({currLign, currCol + 1, 114});
                }
                if(currLign > 0 && directions[currLign][currCol - 1][0] == 48){
                    directions[currLign][currCol - 1][0] = 108;
                    stackPath.push({currLign, currCol - 1, 108});
                }
            }
        }
    }
    int res{0};
    for(int i = 0; i <= energized.size() - 1; i++){
        for(int j = 0; j <= energized[0].size() - 1; j++){
            if(energized[i][j] == 35){
                std::cout << "lign" << i << "\n";
                std::cout << "col" << j << "\n";
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}