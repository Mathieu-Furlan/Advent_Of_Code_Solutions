#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <queue>
#include <unordered_map>

int res{0};
std::vector<std::vector<int>> matrix;                                   //  la matrice contient des entiers pour pouvoir numéroter les nodes dans la matrice
std::unordered_map<int, std::unordered_map<int, int>> graph;

void trackPath(int pathLength, int node, std::vector<int>& visited){
    if(node == 2){
        if(pathLength > res){
            res = pathLength;
        }
        return;
    }
    for(auto& [neighbour, dist] : graph.at(node)){
        if(!visited[neighbour - 1]){
            visited[neighbour - 1] = 1; 
            trackPath(pathLength + dist, neighbour, visited);
            visited[neighbour - 1] = 0;
        }
    }
    return;
}

std::array<int, 3> findRealStartingAndEndingPoints(std::array<int, 2> current){
    std::stack<std::array<int, 2>> lookForBeginning;
    lookForBeginning.push(current);
    int steps{0};
    while(lookForBeginning.size() > 0){
        int currLign{lookForBeginning.top()[0]};
        int currCol{lookForBeginning.top()[1]};
        matrix[currLign][currCol] = -1;
        lookForBeginning.pop();
        if(currLign < matrix.size() - 1 && matrix[currLign + 1][currCol] == 0){
            lookForBeginning.push({currLign + 1, currCol});
        }
        if(currLign > 0 && matrix[currLign - 1][currCol] == 0){
            lookForBeginning.push({currLign - 1, currCol});
        }
        if(currCol < matrix[0].size() - 1 && matrix[currLign][currCol + 1] == 0){
            lookForBeginning.push({currLign, currCol + 1});
        }
        if(currCol > 0 && matrix[currLign][currCol - 1] == 0){
            lookForBeginning.push({currLign, currCol - 1});
        }
        if(lookForBeginning.size() > 1){
            return {currLign, currCol, steps};
        }
        else steps++;
    }
    return {-1, -1, steps};
}

void pathBetweenEveryJunction(int firstNodeLine, int firstNodeCol, int lastNodeLine, int lastNodeCol){
    matrix[firstNodeLine][firstNodeCol] = 1;                                // 1 est la node de départ
    std::unordered_map<int, int> init;
    init.insert(std::make_pair(firstNodeCol, 0));
    int nodeCounter{3};                                         // on cherche toutes les nodes et on leur attribue un numéro
    std::stack<std::array<int, 3>> processNodes{{{1, firstNodeLine, firstNodeCol}, {2, lastNodeLine, lastNodeCol}}};
    for(int i = 1; i < matrix.size() - 1; i++){
        for(int j = 1; j < matrix[0].size() - 1; j++){
            if(matrix[i][j] == 0){
                int neighbors{0};
                if(i < matrix.size() - 1 && matrix[i + 1][j] == 0){
                    neighbors++;
                }
                if(i > 0 && matrix[i - 1][j] == 0){
                    neighbors++;
                }
                if(j < matrix[0].size() - 1 && matrix[i][j + 1] == 0){
                    neighbors++;
                }
                if(j > 0 && matrix[i][j - 1] == 0){
                    neighbors++;
                }
                if(neighbors > 2){                                          // s'il y a plus de deux possibilités c'est une node du graphique
                    graph.insert(std::make_pair(nodeCounter, std::unordered_map<int, int>{}));
                    processNodes.push({nodeCounter, i, j});
                    matrix[i][j] = nodeCounter;
                    nodeCounter++;
                }
            }
        }
    }
    graph.insert(std::make_pair(1, std::unordered_map<int, int>{}));
    graph.insert(std::make_pair(2, std::unordered_map<int, int>{}));
    while(processNodes.size() > 0){
        std::array<int, 3> currNode{processNodes.top()};
        int nodeNumber{currNode[0]};
        int currLign{currNode[1]};
        int currCol{currNode[2]};
        processNodes.pop();
        std::vector<std::vector<int>> matrixCopy{matrix};
        matrixCopy[currLign][currCol] = -1;
        std::queue<std::array<int, 2>> searchNeighbours;
        if(currLign < matrix.size() - 1 && matrix[currLign + 1][currCol] == 0){
            searchNeighbours.push({currLign + 1, currCol});
        }
        if(currLign > 0 && matrix[currLign - 1][currCol] == 0){
            searchNeighbours.push({currLign - 1, currCol});
        }
        if(currCol < matrix[0].size() - 1 && matrix[currLign][currCol + 1] == 0){
            searchNeighbours.push({currLign, currCol + 1});
        }
        if(currCol > 0 && matrix[currLign][currCol - 1] == 0){
            searchNeighbours.push({currLign, currCol - 1});
        }
        int distance{1};
        while(searchNeighbours.size() > 0){
            long unsigned step{searchNeighbours.size()};
            distance++;
            while(step > 0 && searchNeighbours.size() > 0){
                std::array<int, 2> currNode{searchNeighbours.front()};
                searchNeighbours.pop();
                matrixCopy[currNode[0]][currNode[1]] = -1;
                if(currNode[0] < matrix.size() - 1 && matrixCopy[currNode[0] + 1][currNode[1]] >= 0){
                    if(matrixCopy[currNode[0] + 1][currNode[1]] == 0){
                        searchNeighbours.push({currNode[0] + 1, currNode[1]});
                    }
                    else{
                        if(graph.at(nodeNumber).find(matrixCopy[currNode[0] + 1][currNode[1]]) == graph.at(nodeNumber).end()){
                            graph.at(nodeNumber).insert(std::make_pair(matrixCopy[currNode[0] + 1][currNode[1]], distance));
                        }
                    } 
                }
                if(currNode[0] > 0 && matrixCopy[currNode[0] - 1][currNode[1]] >= 0){
                    if(matrixCopy[currNode[0] - 1][currNode[1]] == 0){
                        searchNeighbours.push({currNode[0] - 1, currNode[1]});
                    }
                    else{
                        if(graph.at(nodeNumber).find(matrixCopy[currNode[0] - 1][currNode[1]]) == graph.at(nodeNumber).end()){
                            graph.at(nodeNumber).insert(std::make_pair(matrixCopy[currNode[0] - 1][currNode[1]], distance));
                        }
                    }
                }
                if(currNode[1] < matrix[0].size() - 1 && matrixCopy[currNode[0]][currNode[1] + 1] >= 0){
                    if(matrixCopy[currNode[0]][currNode[1] + 1] == 0){
                        searchNeighbours.push({currNode[0], currNode[1] + 1});
                    }
                    else{
                        if(graph.at(nodeNumber).find(matrixCopy[currNode[0]][currNode[1] + 1]) == graph.at(nodeNumber).end()){
                            graph.at(nodeNumber).insert(std::make_pair(matrixCopy[currNode[0]][currNode[1] + 1], distance));
                        }
                    }
                }
                if(currNode[1] > 0 && matrixCopy[currNode[0]][currNode[1] - 1] >= 0){
                    if(matrixCopy[currNode[0]][currNode[1] - 1] == 0){
                        searchNeighbours.push({currNode[0], currNode[1] - 1});
                    }
                    else{
                        if(graph.at(nodeNumber).find(matrixCopy[currNode[0]][currNode[1] - 1]) == graph.at(nodeNumber).end()){
                            graph.at(nodeNumber).insert(std::make_pair(matrixCopy[currNode[0]][currNode[1] - 1], distance));
                        }
                    }
                }
                step--;
            }
        }
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    int startColumn{0};
    int endLine{0};
    getline(file, s);
    std::vector<int> tempInit;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '#'){
            tempInit.push_back(-1);
        }
        else tempInit.push_back(0);
        if(s[i] == '.'){
            startColumn = i;
        }
    }
    matrix.push_back(tempInit);
    while(getline(file, s)){
        std::vector<int> temp;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '.' || s[i] == 'v' || s[i] == '<' || s[i] == '>'){
                temp.push_back(0);
            }
            else temp.push_back(-1);
        }
        matrix.push_back(temp);
        endLine++;
    }
    int endColumn;
    for(int i = 0; i < matrix[0].size(); i++){
        if(matrix[endLine][i] == 0){
            endColumn = i;
        }
    }
    std::array<int, 3>startCoordinates{findRealStartingAndEndingPoints({0, startColumn})};
    int stepsBeforeFirstNode{startCoordinates[2]};
    std::array<int, 3>endCoordinates{findRealStartingAndEndingPoints({endLine, endColumn})};
    int realEndLine{endCoordinates[0]};
    int realEndCol{endCoordinates[1]};
    matrix[realEndLine][realEndCol] = 2;                                                    // 2 est la node d'arrivée
    std::unordered_map<int, int> init;
    init.insert(std::make_pair(realEndCol, 1));
    int stepsAfterLastNode{endCoordinates[2]};
    pathBetweenEveryJunction(startCoordinates[0], startCoordinates[1], realEndLine, realEndLine);
    unsigned long graphSize{graph.size()};
    std::vector<int> visited;
    for(int i = 0; i < graphSize; i++){
        visited.push_back(0);
    }
    trackPath(0, 1, visited);
    std::cout << res + stepsBeforeFirstNode + stepsAfterLastNode << "\n";
    return 0;
}