#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<char, 7>> chamber;
    std::string gasJets;
    while(getline(file, s)){
        if(s.length() > 0){
            gasJets = s;
        }
    }
    const unsigned long GAS_JETS_SIZE{gasJets.length()};
    std::array<int, 5> rocksShapes{0, 1, 2, 3, 4};
    int fallenRocks{0};
    int rockType{0};
    std::array<char, 7> firstLevel{'#', '#', '#', '#', '#', '#', '#'};
    chamber.push_back(firstLevel);                                      // le niveau 0
    std::array<char, 7> level{'.', '.', '.', '.', '.', '.', '.'};
    int jetIndex{0};
    int highestLevel{0};
    while(fallenRocks < 2022){
        fallenRocks++;
        int fallingRock{rockType};
        rockType++;
        if(rockType == 5){                                          // 5 types de roches
            rockType = 0;
        }
        std::vector<std::array<int, 2>> rockParts;
        if(fallingRock == 0){                                                              // ####
            rockParts.push_back({2, highestLevel + 4});
            rockParts.push_back({3, highestLevel + 4});
            rockParts.push_back({4, highestLevel + 4});
            rockParts.push_back({5, highestLevel + 4});
        }
        else if(fallingRock == 1){                                                           // .#.
            rockParts.push_back({2, highestLevel + 5});                                      // ###   
            rockParts.push_back({3, highestLevel + 4});                                      // .#.
            rockParts.push_back({3, highestLevel + 5});
            rockParts.push_back({3, highestLevel + 6});
            rockParts.push_back({4, highestLevel + 5});
        }
        else if(fallingRock == 2){                                                           // ..#
            rockParts.push_back({2, highestLevel + 4});                                      // ..#   
            rockParts.push_back({3, highestLevel + 4});                                      // ###
            rockParts.push_back({4, highestLevel + 4});
            rockParts.push_back({4, highestLevel + 5});
            rockParts.push_back({4, highestLevel + 6});
        }
        else if(fallingRock == 3){                                                           // #
            rockParts.push_back({2, highestLevel + 4});                                      // #   
            rockParts.push_back({2, highestLevel + 5});                                      // #
            rockParts.push_back({2, highestLevel + 6});                                      // #
            rockParts.push_back({2, highestLevel + 7});
        }
        else if(fallingRock == 4){                                                           // ##
            rockParts.push_back({2, highestLevel + 4});                                      // ##   
            rockParts.push_back({2, highestLevel + 5});
            rockParts.push_back({3, highestLevel + 4});
            rockParts.push_back({3, highestLevel + 5});
        }
        for(int i = jetIndex; i <= GAS_JETS_SIZE - 1; i = (i + 1) % GAS_JETS_SIZE){         // on parcourt les mouvements tant que la roche n'est pas bloquée
            if(gasJets[i] == '<'){                      // si c'est gauche
                bool movable{true};
                for(auto& part : rockParts){
                    if(part[0] - 1 < 0){                // si on est bloqué à gauche par le mur
                        movable = false;
                    }
                    else if(part[1] < chamber.size() && chamber[part[1]][part[0] - 1] == '#'){   // si on est bloqué par une roche
                        movable = false;
                    }
                }
                if(movable){
                    for(auto& part : rockParts){
                        part[0]--;
                    }
                }
            }
            else if(gasJets[i] == '>'){                     // si c'est droite
                bool movable{true};
                for(auto& part : rockParts){
                    if(part[0] + 1 > 6){                    // si on est bloqué à droite par le mur
                        movable = false;
                    }
                    else if(part[1] < chamber.size() && chamber[part[1]][part[0] + 1] == '#'){    // si on est bloqué par une roche
                        movable = false;
                    }
                }
                if(movable){
                    for(auto& part : rockParts){
                        part[0]++;
                    }
                }
            }
            bool canFall{true};
            for(auto& part : rockParts){
                if(part[1] <= chamber.size() && chamber[part[1] - 1][part[0]] == '#'){
                    canFall = false;     // si il y a une roche en dessous
                }
            }
            if(!canFall){
                for(auto& part : rockParts){
                    if(part[1] > chamber.size() - 1){
                        while(chamber.size() - 1 < part[1]){        // si la roche dépasse le niveau maximal du gouffre
                            chamber.push_back(level);
                            highestLevel++;                         // on augment le niveau maximum atteint
                        }
                    }
                    chamber[part[1]][part[0]] = '#';
                }
                jetIndex = i < GAS_JETS_SIZE - 1 ? i + 1 : 0;
                break;
            }
            else for(auto& part : rockParts){
                part[1]--;
            }
        }
        if(fallenRocks < 10){
            std::cout << "jetIndex " << jetIndex << "\n";
            std::cout << "fallenRocks " << fallenRocks << "\n";
            for(int i = chamber.size() - 1; i >= 0; i--){
                for(int j = 0; j <= 6; j++){
                    std::cout << chamber[i][j];
                }
                std::cout << "\n";
            }
        }
    }
    std::cout << highestLevel << "\n";
    return 0;
}