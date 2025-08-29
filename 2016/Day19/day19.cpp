#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::vector<int> elves;
    for(int i = 1; i <= 3014387; i++){
        elves.push_back(i);
    }
    while(elves.size() > 1){
        int startingIndex{0};
        if(elves.size() % 2 != 0){
            startingIndex = 2;
        }
        std::vector<int> nextRoundElves;
        for(int i = startingIndex; i < elves.size(); i = i + 2){
            nextRoundElves.push_back(elves[i]);
        }
        elves = nextRoundElves;
    }
    std::cout << elves[0] << "\n";
    return 0;
}