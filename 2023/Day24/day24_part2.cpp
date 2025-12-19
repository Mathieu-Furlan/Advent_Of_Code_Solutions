#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <eigen3/Eigen/Dense>           // la librairie eigen doit être installée

void equationFormula(std::array<long double, 6>& stone0, std::array<long double, 6>& stoneN, Eigen::Matrix<long double, 6, 6>& pushToA, Eigen::Matrix<long double, 6, 1>& pushToB, int index){
    pushToA(index, 0) = stone0[4] - stoneN[4];
    pushToA(index, 1) = stoneN[3] - stone0[3];
    pushToA(index, 2) = 0;
    pushToA(index, 3) = stoneN[1] - stone0[1];
    pushToA(index, 4) = stoneN[0] - stone0[0];
    pushToA(index, 5) = 0;
    pushToB(index, 0) = stone0[0] * stone0[4] - stone0[1] * stone0[3] - stoneN[0] * stoneN[4] + stoneN[1] * stoneN[3];
    pushToA(index + 1, 0) = stone0[5] - stoneN[5];
    pushToA(index + 1, 1) = 0;
    pushToA(index + 1, 2) = stoneN[3] - stone0[3];
    pushToA(index + 1, 3) = stoneN[2] - stone0[2];
    pushToA(index + 1, 4) = 0;
    pushToA(index + 1, 5) = stone0[0] - stoneN[0];
    pushToB(index + 1) = stone0[0] * stone0[5] - stone0[2] * stone0[3] - stoneN[0] * stoneN[5] + stoneN[2] * stoneN[3];
    return;
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::array<std::array<long double, 6>, 4> hailStones;
    int lineCounter{0};
    while(getline(file, s) && lineCounter < 4){
        std::string numBuilder;
        bool comma{false};
        bool comma2{false};
        bool comma3{false};
        bool comma4{false};
        long double x;
        long double y;
        long double z;
        int vx;
        int vy;
        int vz;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == ',' || s[i] == '@'){
                if(!comma){
                    x = std::stol(numBuilder);
                    std::cout.setf(std::ios::fixed);
                    std::cout << x << "\n";
                    numBuilder.clear();
                    comma = true;
                    i++;
                }
                else if(!comma2){
                    y = std::stol(numBuilder);
                    std::cout << y << "\n";
                    numBuilder.clear();
                    comma2 = true;
                    i++;
                }
                else if(!comma3){
                    z = std::stol(numBuilder);
                    std::cout << z << "\n";
                    numBuilder.clear();
                    comma3 = true;
                    i++;
                }
                else if(!comma4){
                    vx = stoi(numBuilder);
                    std::cout << "vx: " << vx << "\n";
                    numBuilder.clear();
                    comma4 = true;
                    i++;
                }
                else{
                    vy = stoi(numBuilder);
                    std::cout << "vy: " << vy << "\n";
                    numBuilder.clear();
                    i++;
                }
            }
            else numBuilder += s[i];
        }
        vz = stoi(numBuilder);
        std::cout << "vz: " << vz << "\n";
        std::array<long double, 6> tempPosVel{x, y, z, (long double)vx, (long double)vy, (long double)vz};
        hailStones[lineCounter] = tempPosVel;
        lineCounter++;
    }
    Eigen::Matrix<long double, 6, 6> matrixA;
    Eigen::Matrix<long double, 6, 1> vectorB;
    int index{0};
    for(int i = 1; i < 4; i++){
        equationFormula(hailStones[0], hailStones[i], matrixA, vectorB, index);
        index += 2;
    }
    std::cout << matrixA << "\n";
    Eigen::Matrix<long double, 6, 1> cramerRule = matrixA.colPivHouseholderQr().solve(vectorB);      // la règle de Cramer
    std::cout << cramerRule << "\n";
    long long res = std::llround(cramerRule(0)) + std::llround(cramerRule(1)) + std::llround(cramerRule(2));
    std::cout << res << "\n";
    return 0;
}