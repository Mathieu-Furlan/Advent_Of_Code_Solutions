#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    const int TARGETROW{2000000};
    std::unordered_set<int> reachRow;
    std::unordered_set<int> beaconsTarget;               // les beacons sur la ligne cible
    while(getline(file, s)){
        std::string valueBuilder;
        int valSelector{0};
        int x1;
        int y1;
        int x2;
        int y2;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == '-' || s[i] > 47 && s[i] < 58){
                valueBuilder += s[i];
                int index{i + 1};
                while(s[index] > 47 && s[index] < 58){
                    valueBuilder += s[index];
                    index++;
                    i++;
                }
                if(valSelector == 0){
                    x1 = std::stoi(valueBuilder);
                    valSelector++;
                    valueBuilder.clear();
                }
                else if(valSelector == 1){
                    y1 = std::stoi(valueBuilder);
                    valSelector++;
                    valueBuilder.clear();
                }
                else if(valSelector == 2){
                    x2 = std::stoi(valueBuilder);
                    valSelector++;
                    valueBuilder.clear();
                }
                else if(valSelector == 3){
                    y2 = std::stoi(valueBuilder);
                    valSelector++;
                    valueBuilder.clear();
                }
            }
        }
        if(y2 == TARGETROW){
            beaconsTarget.insert(x2);
        }
        int distance{std::abs(x2 - x1) + std::abs(y2 - y1)};      // la distance entre le beacon et le sensor
        if(y1 < TARGETROW && y1 + distance >= TARGETROW || y1 > TARGETROW && y1 - distance <= TARGETROW){
            reachRow.insert(x1);              // on ajoute la colonne sur laquelle se trouve le sensor
            int range{1};
            int stopLoop;
            if(y1 < TARGETROW){
                stopLoop = y1 + distance - TARGETROW;       // le nombre de points atteignables sur la ligne cible
            }
            else stopLoop = TARGETROW + distance - y1;      // le nombre de points atteignables sur la ligne cible
            for(int j = 0; j < stopLoop; j++){
                reachRow.insert(x1 + range);
                reachRow.insert(x1 - range);
                range++;
            }
        }
    }
    int res{0};
    for(auto& elem : reachRow){
        if(beaconsTarget.find(elem) == beaconsTarget.end()){    // si il y a des beacons qui ont été comptés dans le résultat
            res++;
        }
    }
    std::cout << res << "\n";
    return res;
}