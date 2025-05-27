#include <iostream>
#include <array>
#include <cmath>
#include <string>
#include <unordered_map>
#include <numeric>

int main(){
    int steps{0};
    std::array<int, 6> moonA{-8, -10, 0, 0, 0, 0};
    std::array<int, 6> moonB{5, 5, 10, 0, 0, 0};
    std::array<int, 6> moonC{2, -7, 3, 0, 0, 0};
    std::array<int, 6> moonD{9, -8, -3, 0, 0, 0};
    std::array<std::array<int, 6>, 4> moons{moonA, moonB, moonC, moonD};
    std::unordered_map<std::string, int> pastStatesX;
    std::unordered_map<std::string, int> pastStatesY;
    std::unordered_map<std::string, int> pastStatesZ;
    pastStatesX.insert(std::make_pair("-8 0 5 0 2 0 9 0 ", steps));           // l'état de départ
    pastStatesY.insert(std::make_pair("-10 0 5 0 -7 0 -8 0 ", steps));
    pastStatesZ.insert(std::make_pair("0 0 10 0 3 0 -3 0 ", steps));
    int cycleX{0};
    int cycleY{0};
    int cycleZ{0};
    int startLastCycle{0};
    bool repetition{false};
    while(!repetition){                   // pour chaque étape
        for(int i = 0; i < 3; i++){                 // pour chaque axe
            for(int j = 0; j < 4; j++){             // pour chaque lune
                for(int k = 0; k < 4; k++){         // pour chaque élément de chaque axe de chaque lune
                    if(k != j && moons[j][i] < moons[k][i]){
                        moons[j][i + 3]++;
                    }
                    else if(k != j && moons[j][i] > moons[k][i]){
                        moons[j][i + 3]--;
                    }
                }
            }
            for(int m = 0; m < 4; m++){                 // on met à jour les positions de chaque lune
                moons[m][i] += moons[m][i + 3];
            }
        }
        steps++;
        std::string xAxis;
        std::string yAxis;
        std::string zAxis;
        for(auto& moon : moons){
            xAxis += std::to_string(moon[0]) + ' ' + std::to_string(moon[3]) + ' ';
            yAxis += std::to_string(moon[1]) + ' ' + std::to_string(moon[4]) + ' ';
            zAxis += std::to_string(moon[2]) + ' ' + std::to_string(moon[5]) + ' ';
        }
        if(cycleX == 0 && pastStatesX.find(xAxis) != pastStatesX.end()){            // si on trouve un cycle pour x
            cycleX = steps - pastStatesX.at(xAxis);
            if(pastStatesX.at(xAxis) > startLastCycle){
                startLastCycle = pastStatesX.at(xAxis);
            }
            std::cout << xAxis << "\n";
            std::cout << "cycleX " << cycleX << "\n";
        }
        else pastStatesX.insert(std::make_pair(xAxis, steps));
        if(cycleY == 0 && pastStatesY.find(yAxis) != pastStatesY.end()){            // si on trouve un cycle pour y
            cycleY = steps - pastStatesY.at(yAxis);
            if(pastStatesY.at(yAxis) > startLastCycle){
                startLastCycle = pastStatesY.at(yAxis);
            }
            std::cout << yAxis << "\n";
            std::cout << "cycleY " << cycleY << "\n";
        }
        else pastStatesY.insert(std::make_pair(yAxis, steps));
        if(cycleZ == 0 && pastStatesZ.find(zAxis) != pastStatesZ.end()){            // si on trouve un cycle pour z
            cycleZ = steps - pastStatesZ.at(zAxis);
            if(pastStatesZ.at(zAxis) > startLastCycle){
                startLastCycle = pastStatesZ.at(zAxis);
            }
            std::cout << zAxis << "\n";
            std::cout << "cycleZ " << cycleZ << "\n";
        }
        else pastStatesZ.insert(std::make_pair(zAxis, steps));
        if(cycleX != 0 && cycleY != 0 && cycleZ != 0){
            repetition = true;
        }
    }
    int res{std::lcm(std::lcm(cycleX, cycleY), cycleZ)};
    std::cout << startLastCycle << "\n";
    std::cout << res << "\n";
    return 0;
}