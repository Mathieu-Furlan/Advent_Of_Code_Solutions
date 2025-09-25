#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>

int excavateGeodes(int minutes, int ore, int oreRobots, int oreRobCost, int clay, int clayRobots, int clayRobCost, int obsidian, std::array<int, 2>& obsidianRobCost, int obsidianRobots, int geode, int geodeRobots, std::array<int, 2>& geodeRobCost, int oreMax, int clayMax, int obsidianMax, int prevBuilt){
    double fastForward1{std::ceil((oreRobCost - ore) / oreRobots) - 1};
    double fastForward2{std::ceil((clayRobCost - ore) / oreRobots) - 1};
    double fastForward3;
    double fastForward4;
    if(clayRobots > 0 && obsidianRobots < obsidianMax){
        fastForward3 = std::max(std::ceil((obsidianRobCost[0] - ore) / oreRobots), std::ceil((obsidianRobCost[1] - clay) / clayRobots)) - 1;
    }
    if(obsidianRobots > 0){
        fastForward4 = std::max(std::ceil((geodeRobCost[0] - ore) / oreRobots), std::ceil((geodeRobCost[1] - obsidian) / obsidianRobots)) - 1;
    }
    ore += oreRobots;
    clay += clayRobots;
    obsidian += obsidianRobots;
    geode += geodeRobots;
    if(prevBuilt == 1){
        ore--;
    }
    else if(prevBuilt == 2){
        clay--;
    }
    else if(prevBuilt == 3){
        obsidian--;
    }
    else if(prevBuilt == 4){
        geode--;
    }
    if(minutes == 32){
        return geode;
    }
    int choice1{0};
    int choice2{0};
    int choice3{0};
    int choice4{0};
    if(minutes < 31){
        if(oreRobots < oreMax && minutes + fastForward1 + 1 <= 32){
            choice1 = excavateGeodes(minutes + fastForward1 + 1, ore + oreRobots * fastForward1 - oreRobCost, oreRobots + 1, oreRobCost, clay + clayRobots * fastForward1, clayRobots, clayRobCost, obsidian + obsidianRobots * fastForward1, obsidianRobCost, obsidianRobots, geode + geodeRobots * fastForward1, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax, 1);
        }
        if(clayRobots < clayMax && minutes < 30 && minutes + fastForward2 + 1 <= 32){
            choice2 = excavateGeodes(minutes + fastForward2 + 1, ore + oreRobots * fastForward2 - clayRobCost, oreRobots, oreRobCost, clay + clayRobots * fastForward2, clayRobots + 1, clayRobCost, obsidian + obsidianRobots * fastForward2, obsidianRobCost, obsidianRobots, geode + geodeRobots * fastForward2, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax, 2);
        }
        if(clayRobots > 0 && obsidianRobots < obsidianMax && minutes + fastForward3 + 1 <= 32){
            choice3 = excavateGeodes(minutes + fastForward3 + 1, ore + oreRobots * fastForward3 - obsidianRobCost[0], oreRobots, oreRobCost, clay + clayRobots * fastForward3 - obsidianRobCost[1], clayRobots, clayRobCost, obsidian + obsidianRobots * fastForward3, obsidianRobCost, obsidianRobots + 1, geode + geodeRobots * fastForward3, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax, 3);
        }
    }
    if(obsidianRobots > 0 && minutes + fastForward4 + 1 <= 32){
        choice4 = excavateGeodes(minutes + fastForward4 + 1, ore + oreRobots * fastForward4 - geodeRobCost[0], oreRobots, oreRobCost, clay + clayRobots * fastForward4, clayRobots, clayRobCost, obsidian + obsidianRobots * fastForward4 - geodeRobCost[1], obsidianRobCost, obsidianRobots, geode + geodeRobots * fastForward4, geodeRobots + 1, geodeRobCost, oreMax, clayMax, obsidianMax, 4);
    }
    int fastForward{32 - minutes};
    int choice5{excavateGeodes(minutes + fastForward, ore + oreRobots * fastForward, oreRobots, oreRobCost, clay + clayRobots * fastForward, clayRobots, clayRobCost, obsidian + obsidianRobots * fastForward, obsidianRobCost, obsidianRobots, geode + geodeRobots * fastForward, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax, 0)};
    return std::max(choice5, std::max(choice4, std::max(choice3, std::max(choice1, choice2))));
}

int main(){
    std::ifstream file("inputtest");
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
                    oreRobotCost = std::stoi(val);
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
        int quality{excavateGeodes(1, 0, 1, oreRobotCost, 0, 0, clayRobotCost, 0, obsidianCost, 0, 0, 0, geodeCost, maxOre, maxClay, maxObsidian, 1)};
        std::cout << "quality " << quality << "\n";
        res += (quality * blueprintNumber);
    }
    std::cout << res << "\n";
    return 0;
}