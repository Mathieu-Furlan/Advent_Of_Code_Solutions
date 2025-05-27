#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>

int excavateGeodes(int minutes, int ore, int oreRobots, int oreRobCost, int clay, int clayRobots, int clayRobCost, int obsidian, std::array<int, 2>& obsidianRobCost, int obsidianRobots, int geode, int geodeRobots, std::array<int, 2>& geodeRobCost, int oreMax, int clayMax, int obsidianMax){
    bool firstChoice{false};
    bool secondChoice{false};
    bool thirdChoice{false};
    bool fourthChoice{false};
    if(minutes < 23){                                   // un robot créé la dernière minute n'a aucun intérêt
        if(ore >= oreRobCost && oreRobots < oreMax){
            firstChoice = true;
        }
        if(ore >= clayRobCost && clayRobots < clayMax && minutes < 22){   // minutes < 22 car il faut ensuite 1 minute pour un osidian robot et 1 minute pour geode robot
            secondChoice = true;
        }
        if(ore >= obsidianRobCost[0] && clay >= obsidianRobCost[1] && obsidianRobots < obsidianMax){
            thirdChoice = true;
        }
    }
    if(ore >= geodeRobCost[0] && obsidian >= geodeRobCost[1]){
        fourthChoice = true;
    }
    ore += oreRobots;
    clay += clayRobots;
    obsidian += obsidianRobots;
    geode += geodeRobots;
    if(minutes == 24){
        return geode;
    }
    int choice1{0};
    int choice2{0};
    int choice3{0};
    int choice4{0};
    if(firstChoice){
        choice1 = excavateGeodes(minutes + 1, ore - oreRobCost, oreRobots + 1, oreRobCost, clay, clayRobots, clayRobCost, obsidian, obsidianRobCost, obsidianRobots, geode, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax);
    }
    if(secondChoice){
        choice2 = excavateGeodes(minutes + 1, ore - clayRobCost, oreRobots, oreRobCost, clay, clayRobots + 1, clayRobCost, obsidian, obsidianRobCost, obsidianRobots, geode, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax);
    }
    if(thirdChoice){
        choice3 = excavateGeodes(minutes + 1, ore - obsidianRobCost[0], oreRobots, oreRobCost, clay - obsidianRobCost[1], clayRobots, clayRobCost, obsidian, obsidianRobCost, obsidianRobots + 1, geode, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax);
    }
    if(fourthChoice){
        choice4 = excavateGeodes(minutes + 1, ore - geodeRobCost[0], oreRobots, oreRobCost, clay, clayRobots, clayRobCost, obsidian - geodeRobCost[1], obsidianRobCost, obsidianRobots, geode, geodeRobots + 1, geodeRobCost, oreMax, clayMax, obsidianMax);
    }
    int choice5{excavateGeodes(minutes + 1, ore, oreRobots, oreRobCost, clay, clayRobots, clayRobCost, obsidian, obsidianRobCost, obsidianRobots, geode, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax)};
    return std::max(choice5, std::max(choice4, std::max(choice3, std::max(choice1, choice2))));
}

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
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
                    if(clayRobotCost > maxOre){
                        maxOre = clayRobotCost;
                    }
                    clayRobot = false;
                }
                else if(obsidianRobotOre){
                    obsidianCost[0] = std::stoi(val);
                    if(obsidianCost[0] > maxOre){
                        maxOre = obsidianCost[0];
                    }
                    obsidianRobotOre = false;
                }
                else if(obsidianRobotClay){
                    obsidianCost[1] = std::stoi(val);
                    maxClay = obsidianCost[1];
                    obsidianRobotClay = false;
                }
                else if(geodeRobotOre){
                    geodeCost[0] = std::stoi(val);
                    if(geodeCost[0] > maxOre){
                        maxOre = geodeCost[0];
                    }
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
        int quality{excavateGeodes(1, 0, 1, oreRobotCost, 0, 0, clayRobotCost, 0, obsidianCost, 0, 0, 0, geodeCost, maxOre, maxClay, maxObsidian)};
        std::cout << "quality " << quality << "\n";
        res += (quality * blueprintNumber);
    }
    std::cout << res << "\n";
    return 0;
}