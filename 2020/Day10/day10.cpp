#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<int> adapters;
    while(getline(file, s)){
        adapters.push_back(std::stoi(s));
    }
    std::sort(adapters.begin(), adapters.end());
    int currentJolts{0};
    int difference3{0};
    int difference1{0};
    for(int i = 0; i <= adapters.size() - 1; i++){
        if(adapters[i] - currentJolts == 3){
            difference3++;
        }
        else if(adapters[i] - currentJolts == 1){
            difference1++;
        }
        currentJolts = adapters[i];
    }
    difference3++;        // l'appareil final à une différence de trois par rapport à l'élément le plus élevé
    std::cout << difference1 * difference3 << "\n";
    return 0;
}