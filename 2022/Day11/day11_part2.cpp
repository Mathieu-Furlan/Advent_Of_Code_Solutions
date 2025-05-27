#include <vector>
#include <cmath>
#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>

int main(){
    int rounds{0};                                                                      // ppcm de tous les tests
    const int MODULO{std::lcm(std::lcm(std::lcm(std::lcm(std::lcm(std::lcm(std::lcm(13, 3), 19), 17), 5), 7), 11), 2)};
    std::array<int, 8> inspections;
    std::fill(inspections.begin(), inspections.end(), 0);
    std::array<std::vector<long>, 8> monkeys;                       // int est insuffisant
    std::vector<long> monkey0 = {54, 98, 50, 94, 69, 62, 53, 85};
    std::vector<long> monkey1 = {71, 55, 82};
    std::vector<long> monkey2 = {77, 73, 86, 72, 87};
    std::vector<long> monkey3 = {97, 91};
    std::vector<long> monkey4 = {78, 97, 51, 85, 66, 63, 62};
    std::vector<long> monkey5 = {88};
    std::vector<long> monkey6 = {87, 57, 63, 86, 87, 53};
    std::vector<long> monkey7 = {73, 59, 82, 65};
    monkeys[0] = monkey0;
    monkeys[1] = monkey1;
    monkeys[2] = monkey2;
    monkeys[3] = monkey3;
    monkeys[4] = monkey4;
    monkeys[5] = monkey5;
    monkeys[6] = monkey6;
    monkeys[7] = monkey7;
    for(int i = 0;; i = (i + 1) % 8){
        if(i == 0){
            rounds++;
            if(rounds == 10001){
                break;
            }
        }
        if(i == 0 && monkeys[0].size() > 0){
            for(int j = monkeys[0].size() - 1; j >= 0; j--){
                inspections[0]++;
                monkeys[0][j] *= 13;
                monkeys[0][j] = monkeys[0][j] % MODULO;  // on réduit la taille du nombre en divisant par le ppcm de toutes les valeurs de test
                monkeys[0][j] % 3 == 0 ? monkeys[2].push_back(monkeys[0][j]) : monkeys[1].push_back(monkeys[0][j]);
                monkeys[0].pop_back();
            }
        }
        else if(i == 1 && monkeys[1].size() > 0){
            for(int j = monkeys[1].size() - 1; j >= 0; j--){
                inspections[1]++;
                monkeys[1][j] += 2;
                monkeys[1][j] = monkeys[1][j] % MODULO;
                monkeys[1][j] % 13 == 0 ? monkeys[7].push_back(monkeys[1][j]) : monkeys[2].push_back(monkeys[1][j]);
                monkeys[1].pop_back();
            }
        }
        else if(i == 2 && monkeys[2].size() > 0){
            for(int j = monkeys[2].size() - 1; j >= 0; j--){
                inspections[2]++;
                monkeys[2][j] += 8;
                monkeys[2][j] = monkeys[2][j] % MODULO;
                monkeys[2][j] % 19 == 0 ? monkeys[4].push_back(monkeys[2][j]) : monkeys[7].push_back(monkeys[2][j]);
                monkeys[2].pop_back();
            }
        }
        else if(i == 3 && monkeys[3].size() > 0){
            for(int j = monkeys[3].size() - 1; j >= 0; j--){
                inspections[3]++;
                monkeys[3][j] += 1;
                monkeys[3][j] = monkeys[3][j] % MODULO;
                monkeys[3][j] % 17 == 0 ? monkeys[6].push_back(monkeys[3][j]) : monkeys[5].push_back(monkeys[3][j]);
                monkeys[3].pop_back();
            }
        }
        else if(i == 4 && monkeys[4].size() > 0){
            for(int j = monkeys[4].size() - 1; j >= 0; j--){
                inspections[4]++;
                monkeys[4][j] *= 17;
                monkeys[4][j] = monkeys[4][j] % MODULO;
                monkeys[4][j] % 5 == 0 ? monkeys[6].push_back(monkeys[4][j]) : monkeys[3].push_back(monkeys[4][j]);
                monkeys[4].pop_back();
            }
        }
        else if(i == 5 && monkeys[5].size() > 0){
            for(int j = monkeys[5].size() - 1; j >= 0; j--){
                inspections[5]++;
                monkeys[5][j] += 3;
                monkeys[5][j] = monkeys[5][j] % MODULO;
                monkeys[5][j] % 7 == 0 ? monkeys[1].push_back(monkeys[5][j]) : monkeys[0].push_back(monkeys[5][j]);
                monkeys[5].pop_back();
            }
        }
        else if(i == 6 && monkeys[6].size() > 0){
            for(int j = monkeys[6].size() - 1; j >= 0; j--){
                inspections[6]++;
                monkeys[6][j] *= monkeys[6][j];
                monkeys[6][j] = monkeys[6][j] % MODULO;
                monkeys[6][j] % 11 == 0 ? monkeys[5].push_back(monkeys[6][j]) : monkeys[0].push_back(monkeys[6][j]);
                monkeys[6].pop_back();
            }
        }
        else if(i == 7 && monkeys[7].size() > 0){
            for(int j = monkeys[7].size() - 1; j >= 0; j--){
                inspections[7]++;
                monkeys[7][j] += 6;
                monkeys[7][j] = monkeys[7][j] % MODULO;
                monkeys[7][j] % 2 == 0 ? monkeys[4].push_back(monkeys[7][j]) : monkeys[3].push_back(monkeys[7][j]);
                monkeys[7].pop_back();
            }
        }
    }
    long active1{0};
    long active2{0};
    for(int k = 0; k <= 7; k++){
        if(inspections[k] > active1){
            if(active1 > active2){
                active2 = active1;
            }
            active1 = inspections[k];
        }
        else if(inspections[k] > active2){
            active2 = inspections[k];
        }
    }
    long res{active1 * active2};
    std::cout << res << "\n";
    return res;
}