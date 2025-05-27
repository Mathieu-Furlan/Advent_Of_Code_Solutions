#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<int, 2>> galaxies;
    std::vector<int> emptyLines;
    std::vector<bool> emptyColumns;
    int lines{0};
    getline(file, s);
    bool foundGalaxy{false};
    for(int i = 0; i <= s.length() - 1; i++){
        if(s[i] == 35){
            galaxies.push_back({lines, i});
            foundGalaxy = true;
            emptyColumns.push_back(false);
        }
        else emptyColumns.push_back(true);
    }
    if(!foundGalaxy){
        emptyLines.push_back(lines);
    }
    lines++;
    while(getline(file, s)){
        bool foundGalaxy{false};
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == 35){
                galaxies.push_back({lines, i});
                foundGalaxy = true;
                if(emptyColumns[i] == true){
                    emptyColumns[i] = false;
                }
            }
        }
        if(!foundGalaxy){
            emptyLines.push_back(lines);
        }
        lines++;
    }
    for(int k = 0; k <= galaxies.size() - 1; k++){
        long adjustLines{0};
        long adjustCols{0};
        for(int m = 0; m <= emptyLines.size() - 1; m++){
            if(galaxies[k][0] > emptyLines[m]){
                adjustLines += 999999;
            }
            else break;
        }
        galaxies[k][0] += adjustLines;
        for(int n = 0; n <= emptyColumns.size() - 1; n++){
            if(galaxies[k][1] > n && emptyColumns[n] == true){
                adjustCols += 999999;
            }
        }
        galaxies[k][1] += adjustCols;
    }
    long long res{0};
    for(int i = 0; i <= galaxies.size() - 2; i++){
        for(int j = i + 1; j <= galaxies.size() - 1; j++){
            res += std::abs(galaxies[i][0] - galaxies[j][0]) + std::abs(galaxies[i][1] - galaxies[j][1]);
        }
    }
    std::cout << res << "\n";
    return 0;
}