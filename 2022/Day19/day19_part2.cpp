#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>

int highestNumberGeodes{0};
const int TIME_LIMIT{32};

void excavateGeodes(int minutes, int ore, int oreRobots, int oreRobCost, int clay, int clayRobots, int clayRobCost, int obsidian, std::array<int, 2>& obsidianRobCost, int obsidianRobots, int geode, std::array<int, 2>& geodeRobCost, int oreMax, int clayMax, int obsidianMax){
    if(minutes == TIME_LIMIT){
        highestNumberGeodes = std::max(highestNumberGeodes, geode);
        return;
    }
    if(geode + ((TIME_LIMIT - minutes + 1) * (TIME_LIMIT - minutes)) / 2 <= highestNumberGeodes){       // si on sait qu'on en pourra pas faire mieux que le meilleur résultat jusqu'à présent
        return;
    } 
    if(minutes < TIME_LIMIT - 1){                                   // un robot créé la dernière minute n'a aucun intérêt
        if(ore >= oreRobCost && oreRobots < oreMax){
            excavateGeodes(minutes + 1, ore - oreRobCost + oreRobots, oreRobots + 1, oreRobCost, clay + clayRobots, clayRobots, clayRobCost, obsidian + obsidianRobots, obsidianRobCost, obsidianRobots, geode, geodeRobCost, oreMax, clayMax, obsidianMax);
        }
        if(ore >= clayRobCost && clayRobots < clayMax && minutes < TIME_LIMIT - 2){   // minutes < time limite - 2 car il faut ensuite 1 minute pour un osidian robot et 1 minute pour geode robot
            excavateGeodes(minutes + 1, ore - clayRobCost + oreRobots, oreRobots, oreRobCost, clay + clayRobots, clayRobots + 1, clayRobCost, obsidian + obsidianRobots, obsidianRobCost, obsidianRobots, geode, geodeRobCost, oreMax, clayMax, obsidianMax);
        }
        if(ore >= obsidianRobCost[0] && clay >= obsidianRobCost[1] && obsidianRobots < obsidianMax){
            excavateGeodes(minutes + 1, ore - obsidianRobCost[0] + oreRobots, oreRobots, oreRobCost, clay - obsidianRobCost[1] + clayRobots, clayRobots, clayRobCost, obsidian + obsidianRobots, obsidianRobCost, obsidianRobots + 1, geode, geodeRobCost, oreMax, clayMax, obsidianMax);
        }
    }
    if(ore >= geodeRobCost[0] && obsidian >= geodeRobCost[1]){              // on ajoute directement le nombre de géode qui seront extraites par le nouveau robot
        excavateGeodes(minutes + 1, ore - geodeRobCost[0] + oreRobots, oreRobots, oreRobCost, clay + clayRobots, clayRobots, clayRobCost, obsidian - geodeRobCost[1] + obsidianRobots, obsidianRobCost, obsidianRobots, geode + TIME_LIMIT - minutes, geodeRobCost, oreMax, clayMax, obsidianMax);
    }
    excavateGeodes(minutes + 1, ore + oreRobots, oreRobots, oreRobCost, clay + clayRobots, clayRobots, clayRobCost, obsidian + obsidianRobots, obsidianRobCost, obsidianRobots, geode, geodeRobCost, oreMax, clayMax, obsidianMax);
    return;
}

int main(){
    std::ifstream file("input");
    std::string s;
    int lineCounter{0};
    int res{1};
    while(getline(file, s) && lineCounter < 3){
        lineCounter++;
        int maxOre{0};
        int maxClay{0};
        int maxObsidian{0};
        int blueprintNumber;
        bool blueprint{true};
        int materials;
        bool oreRobot{true};
        int oreRobotCost;
        bool clayRobot{true};
        int clayRobotCost;
        bool obsidianRobotOre{true};
        bool obsidianRobotClay{true};
        std::array<int, 2> obsidianCost;
        bool geodeRobotOre{true};
        bool geodeRobotObsidian{true};
        std::array<int, 2> geodeCost;
        std::string val;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58){
                val += s[i];
                i++;
                if(s[i] > 47 && s[i] < 58){
                    val += s[i];
                }
                if(blueprint){
                    blueprintNumber = std::stoi(val);
                    blueprint = false;
                }
                else if(oreRobot){
                    oreRobotCost = std::stoi(val);  // maxOre ne dépend pas des ore robots car on ne les crée pas pour eux-mêmes
                    oreRobot = false;
                }
                else if(clayRobot){
                    clayRobotCost = std::stoi(val);
                    maxOre = std::max(maxOre, clayRobotCost);
                    clayRobot = false;
                }
                else if(obsidianRobotOre){
                    obsidianCost[0] = std::stoi(val);
                    maxOre = std::max(maxOre, obsidianCost[0]);
                    obsidianRobotOre = false;
                }
                else if(obsidianRobotClay){
                    obsidianCost[1] = std::stoi(val);
                    maxClay = obsidianCost[1];
                    obsidianRobotClay = false;
                }
                else if(geodeRobotOre){
                    geodeCost[0] = std::stoi(val);
                    maxOre = std::max(maxOre, geodeCost[0]);
                    geodeRobotOre = false;
                }
                else if(geodeRobotObsidian){
                    geodeCost[1] = std::stoi(val);
                    maxObsidian = geodeCost[1];
                    geodeRobotObsidian = false;
                }
            val.clear();
            }
        }
        std::cout << "cost ore robot " << oreRobotCost << "\n";
        std::cout << "cost clay robot " << clayRobotCost << "\n";
        std::cout << "cost ore obs robot " << obsidianCost[0] << "\n";
        std::cout << "cost clay obs robot " << obsidianCost[1] << "\n";
        std::cout << "cost ore geode robot " << geodeCost[0] << "\n";
        std::cout << "cost obsidian geode robot " << geodeCost[1] << "\n";
        std::cout << "max ore " << maxOre << "\n";
        std::cout << "max clay " << maxClay << "\n";
        std::cout << "max obsi " << maxObsidian << "\n";
        excavateGeodes(1, 0, 1, oreRobotCost, 0, 0, clayRobotCost, 0, obsidianCost, 0, 0, geodeCost, maxOre, maxClay, maxObsidian);
        std::cout << "quality " << highestNumberGeodes << "\n";
        res *= highestNumberGeodes;
        highestNumberGeodes = 0;
    }
    std::cout << res << "\n";
    return 0;
}