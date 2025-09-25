#include <iostream>
#include <array>

int main(){
    std::array<std::array<int, 2>, 6> discs{{{10, 13}, {15, 17}, {17, 19}, {1, 7}, {0, 5}, {1, 3}}};
    for(int i = 0; i < 6; i++){
        discs[i][0] = (discs[i][0] + i + 1) % discs[i][1];
    }
    int slots{0};
    int time{0};
    while(slots < 6){
        time++;
        for(int i = 0; i < 6; i++){
            discs[i][0] = (discs[i][0] + 1) % discs[i][1];
            if(discs[i][0] == 0){
                slots++;
            }
        }
        if(slots < 6){
            slots = 0;
        }
    }
    std::cout << time << "\n";
    return 0;
}