#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <array>

/*
    queue et vector position sont passés par référence pour que la fonction main puisse voir les modifications
    matrix est passée par valeur pour la conserver telle quelle pour main
*/
void bfsCore(std::queue<std::array<int, 2>>& queuePath, int elemNumber, std::vector<std::vector<char>> matrix, std::vector<std::array<int, 2>>& pathPos){
    for(int i = 0; i <= pathPos.size() - 1; i++){
        matrix[pathPos[i][0]][pathPos[i][1]] = 35;
        std::cout << "pathPos[i][0] " << pathPos[i][0] << "\n";
        std::cout << "pathPos[i][1] " << pathPos[i][1] << "\n";
    }
    pathPos.clear();
    std::cout << "new Step " << "\n";
    while(elemNumber > 0){
        int currLign{queuePath.front()[0]};
        int currCol{queuePath.front()[1]};
        std::cout << "lign " << currLign << "\n";
        std::cout << "column " << currCol << "\n";
        queuePath.pop();
        if(currLign > 0 && matrix[currLign - 1][currCol] == '.'){
            queuePath.push({currLign - 1, currCol});
            pathPos.push_back({currLign - 1, currCol});
            matrix[currLign - 1][currCol] = 35;
        }
        if(currLign < matrix.size() - 1 && matrix[currLign + 1][currCol] == '.'){
            queuePath.push({currLign + 1, currCol});
            pathPos.push_back({currLign + 1, currCol});
            matrix[currLign + 1][currCol] = 35;
        }
        if(currCol < matrix[0].size() - 1 && matrix[currLign][currCol + 1] == '.'){
            queuePath.push({currLign, currCol + 1});
            pathPos.push_back({currLign, currCol + 1});
            matrix[currLign][currCol + 1] = 35;
        }
        if(currCol > 0 && matrix[currLign][currCol - 1] == '.'){
            queuePath.push({currLign, currCol - 1});
            pathPos.push_back({currLign, currCol - 1});
            matrix[currLign][currCol - 1] = 35;
        }
        elemNumber--;
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::vector<char>> matrix;
    int startLign{0};
    int startColumn{0};
    int lign{0};
    while(getline(file, s)){
        std::vector<char> temp;
        for(int i = 0; i <= s.length() - 1; i++){
            temp.push_back(s[i]);
            if(s[i] == 'S'){
                startColumn = i;
                startLign = lign;
                temp[i] = 46;
            }
        }
        matrix.push_back(temp);
        lign++;
    }
    std::queue<std::array<int, 2>> queuePath;
    queuePath.push({startLign, startColumn});
    int elfSteps{0};
    std::vector<std::array<int, 2>> temporaryPos;
    temporaryPos.push_back({startLign, startColumn});
    while(elfSteps < 64 && !queuePath.empty()){           // 64 étapes
        long unsigned elemNumber{queuePath.size()};
        elfSteps++;
        bfsCore(queuePath, elemNumber, matrix, temporaryPos);
    }
    std::cout << queuePath.size() << "\n";
    return queuePath.size();
}