#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

int main(){
    std::ifstream file("input");
    std::string s;
    int rows{0};
    std::vector<std::array<int, 2>> asteroids;
    while(getline(file, s)){
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == '#'){
                asteroids.push_back({rows, i});
            }
        }
        rows++;
    }
    int res{0};
    for(int i = 0; i < asteroids.size(); i++){
        std::unordered_set<std::string> coordinatesInv;
        for(int j = 0; j < asteroids.size(); j++){
            if(j == i){
                continue;
            }
            int diffRow{asteroids[i][0] - asteroids[j][0]};
            int diffCol{asteroids[i][1] - asteroids[j][1]};
            int commonDiv = std::gcd(diffRow, diffCol);
            std::string stringRep{std::to_string(diffRow / commonDiv) + "," + std::to_string(diffCol / commonDiv)};
            coordinatesInv.insert(stringRep);
        }
        int setSize{(int)coordinatesInv.size()};
        res = std::max(res, setSize);
    }
    std::cout << res << "\n";
    return 0;
}