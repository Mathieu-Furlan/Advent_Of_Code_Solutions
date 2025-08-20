#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <array>
#include <iostream>
#include <bitset>

int main(){
    int reached{1};
    int favoriteNumber{1352};
    int steps{-1};                          // -1 car steps est incrémenté en sortant de la boucle while même lorsqu'on a trouvé le résultat
    std::queue<std::array<int, 2>> bfsQueue;
    std::unordered_map<int, std::unordered_set<int>> visitedAndWalls;
    bfsQueue.push({{31, 39}});
    visitedAndWalls.insert(std::make_pair(31, std::unordered_set<int>{39}));
    while(bfsQueue.size() > 0 && steps < 50){
        long unsigned nextMove{bfsQueue.size()};
        while(nextMove > 0){
            std::array<int, 2> currPos{bfsQueue.front()};
            bfsQueue.pop();
            int goingLeft{currPos[0] - 1};              // la matrice est représentée avec les colonnes en premier et ensuite les lignes
            bool goLeft{true};
            if(currPos[0] > 0){
                if(visitedAndWalls.find(goingLeft) == visitedAndWalls.end()){
                    visitedAndWalls.insert(std::make_pair(goingLeft, std::unordered_set<int>{currPos[1]}));
                }
                else if(visitedAndWalls.at(goingLeft).find(currPos[1]) == visitedAndWalls.at(goingLeft).end()){
                    visitedAndWalls.at(goingLeft).insert(currPos[1]);
                }
                else goLeft = false;
                if(goLeft){
                    int wallCheck{goingLeft * goingLeft + 3 * goingLeft + 2 * goingLeft * currPos[1] + currPos[1] + currPos[1] * currPos[1] + favoriteNumber};
                    std::string binaryRep = std::bitset< 64 >(wallCheck).to_string();
                    int ones{0};
                    for(int i = 0; i < binaryRep.length(); i++){
                        if(binaryRep[i] == '1'){
                            ones++;
                        }
                    }
                    if(ones % 2 == 0){
                        bfsQueue.push({goingLeft, currPos[1]});
                        reached++;
                    }
                }
            }
            int goingRight{currPos[0] + 1};
            bool goRight{true};
            if(visitedAndWalls.find(goingRight) == visitedAndWalls.end()){
                visitedAndWalls.insert(std::make_pair(goingRight, std::unordered_set<int>{currPos[1]}));
            }
            else if(visitedAndWalls.at(goingRight).find(currPos[1]) == visitedAndWalls.at(goingRight).end()){
                visitedAndWalls.at(goingRight).insert(currPos[1]);
            }
            else goRight = false;
            if(goRight){
                int wallCheck{goingRight * goingRight + 3 * goingRight + 2 * goingRight * currPos[1] + currPos[1] + currPos[1] * currPos[1] + favoriteNumber};
                std::string binaryRep = std::bitset< 64 >(wallCheck).to_string();
                int ones{0};
                for(int i = 0; i < binaryRep.length(); i++){
                    if(binaryRep[i] == '1'){
                        ones++;
                    }
                }
                if(ones % 2 == 0){
                    bfsQueue.push({goingRight, currPos[1]});
                    reached++;
                }
            }
            int goingTop{currPos[1] - 1};
            bool goTop{true};
            if(currPos[1] > 0){
                if(visitedAndWalls.at(currPos[0]).find(goingTop) == visitedAndWalls.at(currPos[0]).end()){
                    visitedAndWalls.at(currPos[0]).insert(goingTop);
                }
                else goTop = false;
                if(goTop){
                    int wallCheck{currPos[0] * currPos[0] + 3 * currPos[0] + 2 * currPos[0] * goingTop + goingTop + goingTop * goingTop + favoriteNumber};
                    std::string binaryRep = std::bitset< 64 >(wallCheck).to_string();
                    int ones{0};
                    for(int i = 0; i < binaryRep.length(); i++){
                        if(binaryRep[i] == '1'){
                            ones++;
                        }
                    }
                    if(ones % 2 == 0){
                        bfsQueue.push({currPos[0], goingTop});
                        reached++;
                    }
                }
            }
            int goingDown{currPos[1] + 1};
            bool goDown{true};
            if(visitedAndWalls.at(currPos[0]).find(goingDown) == visitedAndWalls.at(currPos[0]).end()){
                visitedAndWalls.at(currPos[0]).insert(goingDown);
            }
            else goDown = false;
            if(goDown){
                int wallCheck{currPos[0] * currPos[0] + 3 * currPos[0] + 2 * currPos[0] * goingDown + goingDown + goingDown * goingDown + favoriteNumber};
                std::string binaryRep = std::bitset< 64 >(wallCheck).to_string();
                int ones{0};
                for(int i = 0; i < binaryRep.length(); i++){
                    if(binaryRep[i] == '1'){
                        ones++;
                    }
                }
                if(ones % 2 == 0){
                    bfsQueue.push({currPos[0], goingDown});
                    reached++;
                }
            }
            nextMove--;
        }
        steps++;
    }
    std::cout << reached << "\n";
    return 0;
}