#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<std::array<int, 40>>> distances;
    while(getline(file, s)){
        std::vector<int> rowCreator;
        std::vector<std::array<int, 40>> distCreator;
        for(int i = 0; i <= s.length() - 1; i++){
            rowCreator.push_back(s[i] - 48);
            std::array<int, 40> pathSums;           // 40 distances par cellules: 10 pour chacune des quatres directions
            std::fill(pathSums.begin(), pathSums.end(), std::numeric_limits<int>::max());
            distCreator.push_back(pathSums);
        }
        matrix.push_back(rowCreator);
        distances.push_back(distCreator);
    }
    std::vector<std::array<int, 4>> distReached;
    distReached.push_back({0, 1, 30, 1});
    distReached.push_back({1, 0, 10, 1});
    for(int i = 0; i < 40; i++){
        distances[0][0][i] = 0;             // la cellule de départ
    }
    for(int i = 0; i < 40; i++){
        distances[1][0][i] = matrix[1][0];          // si on commence par le sud
    }
    for(int i = 0; i < 40; i++){
        distances[0][1][i] = matrix[0][1];          // si on commence l'est
    }
    while(distReached.size() > 0){                  // algorithme de dijkstra
        std::array<int, 4> currentCell;             // currentCell contient les coordonnées ainsi que la direction et le nombre de fois d'affilée où la direction a été suivie
        int minDist{std::numeric_limits<int>::max()};
        int minIndex;
        /*for(int i = 0; i <= distances.size() - 1; i++){
            for(int j = 0; j <= distances[0].size() - 1; j++){
                for(int k = 0; k < 12; k++){
                    if(distances[i][j][k] < 500){
                        std::cout << distances[i][j][k] << " ";
                    }
                }
                std::cout << " | ";
            }
            std::cout << "\n";
        }
        for(int i = 0; i <= distReached.size() - 1; i++){
            std::cout << distReached[i][0] << " " << distReached[i][1] << "\n";
        }*/
        for(int i = 0; i <= distReached.size() - 1; i++){
            if(distances[distReached[i][0]][distReached[i][1]][distReached[i][2] + distReached[i][3] - 1] < minDist){
                minDist = distances[distReached[i][0]][distReached[i][1]][distReached[i][2] + distReached[i][3] - 1];
                minIndex = i;
            }
        }
        currentCell = distReached[minIndex];
        if(currentCell[0] == distances.size() - 1 && currentCell[1] == distances[0].size() - 1){  // si la plus petite valeur correspond à la cellule d'arrivée on sait qu'on ne trouvera pas de chemin ayant une valeur moindre
            std::cout << distances[distances.size() - 1][distances[0].size() - 1][currentCell[2] + currentCell[3] - 1] << "\n";
            return 0;
        }
        distReached.erase(distReached.begin() + minIndex, distReached.begin() + minIndex + 1);
        if(currentCell[0] > 0 && currentCell[2] != 10 && (currentCell[2] != 0 || currentCell[3] < 10)){       // 0 correspond au nord, on vérifie qu'on ne revient pas en arrière et que cela ne fait pas plus de trois fois d'affilée que l'on suit cette direction
            int alt{matrix[currentCell[0] - 1][currentCell[1]]};
            if(currentCell[2] != 0 && currentCell[3] >= 4 && currentCell[0] > 3){
                if(alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1] < distances[currentCell[0] - 1][currentCell[1]][0]){
                    distances[currentCell[0] - 1][currentCell[1]][0] = alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1];
                    distReached.push_back({currentCell[0] - 1, currentCell[1], 0, 1});
                }
            }
            else if(currentCell[2] == 0 && alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1] < distances[currentCell[0] - 1][currentCell[1]][currentCell[2] + currentCell[3]]){
                distances[currentCell[0] - 1][currentCell[1]][currentCell[2] + currentCell[3]] = alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1];
                distReached.push_back({currentCell[0] - 1, currentCell[1], 0, currentCell[3] + 1});
            }
        }
        if(currentCell[0] < matrix.size() - 1 && currentCell[2] != 0 && (currentCell[2] != 10 || currentCell[3] < 10)){       // 10 correspond au sud
            int alt{matrix[currentCell[0] + 1][currentCell[1]]};
            if(currentCell[2] != 10 && currentCell[3] >= 4 && currentCell[0] < matrix.size() - 4){
                if(alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1] < distances[currentCell[0] + 1][currentCell[1]][10]){
                    distances[currentCell[0] + 1][currentCell[1]][10] = alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1];
                    distReached.push_back({currentCell[0] + 1, currentCell[1], 10, 1});
                }
            }
            else if(currentCell[2] == 10 && alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1] < distances[currentCell[0] + 1][currentCell[1]][currentCell[2] + currentCell[3]]){
                distances[currentCell[0] + 1][currentCell[1]][currentCell[2] + currentCell[3]] = alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1];
                distReached.push_back({currentCell[0] + 1, currentCell[1], 10, currentCell[3] + 1});
            }
        }
        if(currentCell[1] > 0 && currentCell[2] != 30 && (currentCell[2] != 20 || currentCell[3] < 10)){           // 20 correspond à l'ouest
            int alt{matrix[currentCell[0]][currentCell[1] - 1]};
            if(currentCell[2] != 20 && currentCell[3] >= 4 && currentCell[1] > 3){
                if(alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1] < distances[currentCell[0]][currentCell[1] - 1][20]){
                    distances[currentCell[0]][currentCell[1] - 1][20] = alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1];
                    distReached.push_back({currentCell[0], currentCell[1] - 1, 20, 1});
                }
            }
            else if(currentCell[2] == 20 && alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1] < distances[currentCell[0]][currentCell[1] - 1][currentCell[2] + currentCell[3]]){
                distances[currentCell[0]][currentCell[1] - 1][currentCell[2] + currentCell[3]] = alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1];
                distReached.push_back({currentCell[0], currentCell[1] - 1, 20, currentCell[3] + 1});
            }
        }
        if(currentCell[1] < matrix[0].size() - 1 && currentCell[2] != 20 && (currentCell[2] != 30 || currentCell[3] < 10)){        // 30 correspond à l'est
            int alt{matrix[currentCell[0]][currentCell[1] + 1]};
            if(currentCell[2] != 30 && currentCell[3] >= 4 && currentCell[1] < matrix[0].size() - 4){
                if(alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1] < distances[currentCell[0]][currentCell[1] + 1][30]){
                    distances[currentCell[0]][currentCell[1] + 1][30] = alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1];
                    distReached.push_back({currentCell[0], currentCell[1] + 1, 30, 1});
                }
            }
            else if(currentCell[2] == 30 && alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] + 1] < distances[currentCell[0]][currentCell[1] + 1][currentCell[2] + currentCell[3]]){
                distances[currentCell[0]][currentCell[1] + 1][currentCell[2] + currentCell[3]] = alt + distances[currentCell[0]][currentCell[1]][currentCell[2] + currentCell[3] - 1];
                distReached.push_back({currentCell[0], currentCell[1] + 1, 30, currentCell[3] + 1});
            }
        }
    }
    for(int i = 0; i < 40; i++){
        std::cout << distances[distances.size() - 1][distances[0].size() - 1][i] << "\n";
    }
    return 0;
}