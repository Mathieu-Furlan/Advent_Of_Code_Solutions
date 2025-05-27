#include <iostream>
#include <array>
#include <cmath>

int main(){
    int res{0};
    std::array<std::array<int, 3>, 9> reindeers {{{27, 5, 132}, {22, 2, 41}, {11, 5, 48},  // deux accolades à l'ouverture
    {28, 5, 134}, {4, 16, 55}, {14, 3, 38}, 
    {3, 21, 40}, {18, 6, 103}, {18, 5, 84}}}; 
    for(int i = 0; i <= reindeers.size() - 1; i++){
        int speed{reindeers[i][0]};
        int timeSpeed{reindeers[i][1]};
        int rest{reindeers[i][2]};
        int cycle{timeSpeed + rest};
        double time{std::floor(2503 / cycle)};
        double distance{time * (speed * timeSpeed)};
        if(2503 - cycle * time >= timeSpeed){         // s'il reste assez de temps pour un déplacement mais pas pour un cycle complet avec le repos
            distance += speed * timeSpeed;
        }
        else{
            for(int j = time; j <= 2503 - cycle * time; j++){  // s'il ne reste pas assez de temps pour un déplacement entier on ajoute seconde par seconde
                distance += speed;
            }
        }
        if(distance > res){
            res = distance;
        }
    }
    std::cout << res << "\n";
    return res;
}