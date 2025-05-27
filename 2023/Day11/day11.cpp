// BFS pas nécessaire, juste la différence entre les coordonnées de chaque point

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
        std::cout << lines << "\n";
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
        int adjustLines{0};
        int adjustCols{0};
        for(int m = 0; m <= emptyLines.size() - 1; m++){
            if(galaxies[k][0] > emptyLines[m]){
                adjustLines++;
            }
            else break;
        }
        galaxies[k][0] += adjustLines;    // ajuster après avoir compté le décalage
        for(int n = 0; n <= emptyColumns.size() - 1; n++){
            if(galaxies[k][1] > n && emptyColumns[n] == true){
                adjustCols++;
            }
        }
        galaxies[k][1] += adjustCols;     // ajuster après avoir compté le décalage
    }
    int res{0};
    for(int i = 0; i <= galaxies.size() - 2; i++){
        for(int j = i + 1; j <= galaxies.size() - 1; j++){
            std::cout << "i0 " << galaxies[i][0] << "\n";
            std::cout << "j0 " << galaxies[j][0] << "\n";
            std::cout << "i1 " << galaxies[i][1] << "\n";
            std::cout << "j1 " << galaxies[j][1] << "\n";
            res += std::abs(galaxies[i][0] - galaxies[j][0]) + std::abs(galaxies[i][1] - galaxies[j][1]);
            std::cout << "res " << res << "\n";
        }
    }
    std::cout << res << "\n";
    return res;
}