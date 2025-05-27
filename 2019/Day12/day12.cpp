#include <iostream>
#include <array>
#include <cmath>

int main(){
    const int STEPS{1000};
    std::array<int, 6> moonA{-13, 14, -7, 0, 0, 0};
    std::array<int, 6> moonB{-18, 9, 0, 0, 0, 0};
    std::array<int, 6> moonC{0, -3, -3, 0, 0, 0};
    std::array<int, 6> moonD{-15, 3, -13, 0, 0, 0};
    std::array<std::array<int, 6>, 4> moons{moonA, moonB, moonC, moonD};
    for(int x = 0; x < STEPS; x++){                   // pour chaque étape
        for(int i = 0; i < 3; i++){                 // pour chaque axe
        std::cout << "axe " << i << "\n";
        std::cout << "moonA " << moons[0][i] << " moonB " << moons[1][i] << " moonC " << moons[2][i] << " moonD " << moons[3][i] << "\n";
        std::cout << "moonA " << moons[0][i + 3] << " moonB " << moons[1][i + 3] << " moonC " << moons[2][i + 3] << " moonD " << moons[3][i + 3] << "\n";
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
    }
    std::array<int, 4> potentialEnergy{0, 0, 0, 0};
    std::array<int, 4> kineticEnergy{0, 0, 0, 0};
    int res{0};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            potentialEnergy[i] += std::abs(moons[i][j]); 
        }
        for(int j = 3; j < 6; j++){
            kineticEnergy[i] += std::abs(moons[i][j]); 
        }
        res += potentialEnergy[i] * kineticEnergy[i];
    }
    std::cout << res << "\n";
    return 0;
}