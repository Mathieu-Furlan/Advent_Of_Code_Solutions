#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<long, 2>> intervals; 
    while(getline(file, s)){
        std::string numBuilder;
        int index{0};
        while(s[index] != '-'){
            numBuilder += s[index];
            index++;
        }
        std::array<long, 2> interval{std::stol(numBuilder)};
        numBuilder.clear();
        index++;
        while(index < s.length()){
            numBuilder += s[index];
            index++;
        }
        interval[1] = std::stol(numBuilder);
        intervals.push_back(interval);
    }
    std::sort(intervals.begin(), intervals.end(), [](const std::array<long, 2>& a, const std::array<long, 2>& b){
        if(a[0] < b[0]){
            return true;
        }
        else return false;
    });
    long res{0};
    if(intervals[0][0] > 0){
        res += intervals[0][0];
    }
    long upperBound{intervals[0][1]};
    for(int i = 1; i < intervals.size(); i++){
        if(intervals[i][0] > intervals[i - 1][1] + 1 && intervals[i][0] > upperBound + 1){
            res += intervals[i][0] - std::max(intervals[i - 1][1], upperBound) - 1;
        }
        upperBound = std::max(upperBound, intervals[i][1]);
    }
    res += 4294967295 - std::max(intervals[intervals.size() - 1][1], upperBound);
    std::cout << res << "\n";
    return 0;
}