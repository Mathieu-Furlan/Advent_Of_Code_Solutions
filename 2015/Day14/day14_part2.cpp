#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>

int main(){
    int res{0};
    std::array<std::array<int, 3>, 9> reindeers {{{27, 5, 132}, {22, 2, 41}, {11, 5, 48},  // deux accolades à l'ouverture
    {28, 5, 134}, {4, 16, 55}, {14, 3, 38}, 
    {3, 21, 40}, {18, 6, 103}, {18, 5, 84}}};
    std::array<int, 9> restReindeers;
    std::fill(restReindeers.begin(), restReindeers.end(), 0);
    std::array<int, 9> distances;
    std::fill(distances.begin(), distances.end(), 0);
    std::array<int, 9> moveReindeers;
    for(int i = 0; i <= moveReindeers.size() - 1; i++){
        moveReindeers[i] = reindeers[i][1];
    }
    std::array<int, 9> scores;
    std::fill(scores.begin(), scores.end(), 0);
    for(int j = 0; j < 2503; j++){
        for(int i = 0; i <= reindeers.size() - 1; i++){
            if(restReindeers[i] > 0){                       // si le temps de repos n'est pas écoulé
                restReindeers[i]--;
                if(restReindeers[i] == 0){
                    moveReindeers[i] = reindeers[i][1];
                }
            }
            else{
                moveReindeers[i]--;                        // si le temps de déplacement n'est pas écoulé
                distances[i] += reindeers[i][0];
                if(moveReindeers[i] == 0){
                    restReindeers[i] = reindeers[i][2];
                }
            }
        }
        int leadingDistance{*std::max_element(distances.begin(), distances.end())};  // valeur maximale du tableau
        for(int k = 0; k <= distances.size() - 1; k++){
            if(distances[k] == leadingDistance){            // pour chaque renne en tête
                scores[k]++;
            }
        }
    }
    std::cout << *std::max_element(scores.begin(), scores.end()) << "\n";
    return 0;
}