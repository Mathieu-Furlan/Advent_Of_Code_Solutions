#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>

int excavateGeodes(int minutes, int ore, int oreRobots, int oreRobCost, int clay, int clayRobots, int clayRobCost, int obsidian, std::array<int, 2>& obsidianRobCost, int obsidianRobots, int geode, int geodeRobots, std::array<int, 2>& geodeRobCost, int oreMax, int clayMax, int obsidianMax){
    if(minutes == 25){
        return geode;
    }
    int choice1{0};
    int choice2{0};
    int choice3{0};
    int choice4{0};
    if(minutes < 23){
        if(oreRobots < oreMax){
            double fastForward{std::ceil((oreRobCost - ore) / oreRobots)};
            if(minutes + fastForward <= 23){
                choice1 = excavateGeodes(minutes + fastForward, ore + oreRobots * fastForward - oreRobCost, oreRobots + 1, oreRobCost, clay + clayRobots * fastForward - 1 * clayRobots, clayRobots, clayRobCost, obsidian + obsidianRobots * fastForward - 1 * obsidianRobots, obsidianRobCost, obsidianRobots, geode + geodeRobots * fastForward - 1 * geodeRobots, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax);
            }
        }
        if(clayRobots < clayMax && minutes < 22){
            double fastForward{std::ceil((clayRobCost - ore) / oreRobots)};
            if(minutes + fastForward <= 22){
                choice2 = excavateGeodes(minutes + fastForward, ore + oreRobots * fastForward - clayRobCost, oreRobots, oreRobCost, clay + clayRobots * fastForward - 1 * clayRobots, clayRobots + 1, clayRobCost, obsidian + obsidianRobots * fastForward - 1 * obsidianRobots, obsidianRobCost, obsidianRobots, geode + geodeRobots * fastForward - 1 * geodeRobots, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax);
            }
        }
        if(clayRobots > 0 && obsidianRobots < obsidianMax){
            double fastForward{std::max(std::ceil((obsidianRobCost[0] - ore) / oreRobots), std::ceil((obsidianRobCost[1] - clay) / clayRobots))};
            if(minutes + fastForward <= 23){
                choice3 = excavateGeodes(minutes + fastForward, ore + oreRobots * fastForward - obsidianRobCost[0], oreRobots, oreRobCost, clay + clayRobots * fastForward - obsidianRobCost[1], clayRobots, clayRobCost, obsidian + obsidianRobots * fastForward - 1 * obsidianRobots, obsidianRobCost, obsidianRobots + 1, geode + geodeRobots * fastForward - 1 * geodeRobots, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax);
            }
        }
    }
    if(minutes < 24 && obsidianRobots > 0){
        double fastForward{std::max(std::ceil(geodeRobCost[0] - ore / oreRobots), std::ceil(geodeRobCost[1] - obsidian / obsidianRobots))};
        if(minutes + fastForward <= 24){
            choice4 = excavateGeodes(minutes + fastForward, ore + oreRobots * fastForward - geodeRobCost[0], oreRobots, oreRobCost, clay + clayRobots * fastForward - 1 * clayRobots, clayRobots, clayRobCost, obsidian + obsidianRobots * fastForward - geodeRobCost[1], obsidianRobCost, obsidianRobots, geode + geodeRobots * fastForward - 1 * geodeRobots, geodeRobots + 1, geodeRobCost, oreMax, clayMax, obsidianMax);
        }
    }
    int fastForward{25 - minutes};
    int choice5{excavateGeodes(minutes + fastForward, ore + oreRobots * fastForward - 1 * oreRobots, oreRobots, oreRobCost, clay + clayRobots * fastForward - 1 * clayRobots, clayRobots, clayRobCost, obsidian + obsidianRobots * fastForward - 1 * obsidianRobots, obsidianRobCost, obsidianRobots, geode + geodeRobots * fastForward - 1 * geodeRobots, geodeRobots, geodeRobCost, oreMax, clayMax, obsidianMax)};
    return std::max(choice5, std::max(choice4, std::max(choice3, std::max(choice1, choice2))));
}

int main(){
    std::ifstream file("inputtest");
    std::string s;
    int res{0};
    int numberOfLign{0};
    while(getline(file, s)){
        numberOfLign++;
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
        int quality{excavateGeodes(1, 0, 1, oreRobotCost, 0, 0, clayRobotCost, 0, obsidianCost, 0, 0, 0, geodeCost, maxOre, maxClay, maxObsidian)};
        std::cout << "quality " << quality << "\n";
        quality *= blueprintNumber;
        res += quality;
    }
    std::cout << res << "\n";
    return 0;
}