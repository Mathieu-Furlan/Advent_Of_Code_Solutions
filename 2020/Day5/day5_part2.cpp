#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <limits>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    int firstSeat{std::numeric_limits<int>::max()};
    int lastSeat{0};
    std::unordered_set<int> idCollection;
    while(getline(file, s)){
        double min{0};
        double max{127};
        int row;
        for(int i = 0; i <= 6; i++){
            if(s[i] == 'F'){
                if(i == 6){
                    row = min;
                }
                else max -= std::ceil((max - min) / 2);
            }
            else if(s[i] == 'B'){
                if(i == 6){
                    row = max;
                }
                else min += std::floor((max - min) / 2) + 1;
            }
        }
        double left{0};
        double right{7};
        int column;
        for(int j = 7; j <= 9; j++){
            if(s[j] == 'R'){
                if(j == 9){
                    column = right;
                }
                else left += std::floor((right - left) / 2) + 1;
            }
            else if(s[j] == 'L'){
                if(j == 9){
                    column = left;
                }
                else right -= std::ceil((right - left) / 2);
            }
        }
        int id{row * 8 + column};
        if(id > lastSeat){
            lastSeat = id;
        }
        if(id < firstSeat){
            firstSeat = id;
        }
        idCollection.insert(id);
    }
    for(int i = firstSeat; i <= lastSeat; i++){
        if(idCollection.find(i - 1) != idCollection.end() && idCollection.find(i + 1) != idCollection.end() && idCollection.find(i) == idCollection.end()){
            std::cout << i << "\n";
        }
    }
    return 0;
}