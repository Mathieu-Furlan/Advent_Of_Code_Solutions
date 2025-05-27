#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

long adaptersChains(int adaptVal, std::vector<long>& memory, std::unordered_set<int>& values, int target){
    if(memory[adaptVal] > 0){
        return memory[adaptVal];
    }
    if(adaptVal == target){
        return 1;
    }
    long plusOne{0};
    long plusTwo{0};
    long plusThree{0};
    if(values.find(adaptVal + 1) != values.end()){
        plusOne = adaptersChains(adaptVal + 1, memory, values, target);
    }
    if(values.find(adaptVal + 2) != values.end()){
        plusTwo = adaptersChains(adaptVal + 2, memory, values, target);
    }
    if(values.find(adaptVal + 3) != values.end()){
        plusThree = adaptersChains(adaptVal + 3, memory, values, target);
    }
    memory[adaptVal] = plusOne + plusTwo + plusThree;
    return memory[adaptVal];
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_set<int> adapters;
    int maxAdapter{-1};
    while(getline(file, s)){
        int number{std::stoi(s)};
        if(number > maxAdapter){
            maxAdapter = number;
        }
        adapters.insert(number);
    }
    adapters.insert(maxAdapter + 3);
    int maxJolts{maxAdapter + 3};
    std::vector<long> mem;
    for(int i = 0; i <= maxJolts; i++){
        mem.push_back(0);
    }
    long res{adaptersChains(0, mem, adapters, maxJolts)};
    std::cout << res << "\n";
    return 0;
}