#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>

int main(){
    const long MIN_INTERVAL{200000000000000};
    const long MAX_INTERVAL{400000000000000};
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<long double, 6>> hailStones;
    int res{0};
    while(getline(file, s)){
        std::string numBuilder;
        bool comma{false};
        long double x;
        long double y;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == ','){
                if(!comma){
                    x = std::stol(numBuilder);
                    numBuilder.clear();
                    comma = true;
                    i++;
                }
                else{
                    y = std::stol(numBuilder);
                    numBuilder.clear();
                    break;
                }
            }
            else numBuilder += s[i];
        }
        int vx;
        int vy;
        for(int i = s.find('@') + 2; i < s.length(); i++){
            if(s[i] == ','){
                if(comma){
                    vx = stoi(numBuilder);
                    numBuilder.clear();
                    comma = false;
                    i++;
                }
                else{
                    vy = stoi(numBuilder);
                    break;
                }
            }
            else numBuilder += s[i];
        }
        long double x2{x + (long double)vx};
        long double y2{y + (long double)vy};
        std::array<long double, 6> temp{x, y, x2, y2, (long double)vx, (long double)vy};
        hailStones.push_back(temp);
    }
    for(int i = 0; i < hailStones.size() - 1; i++){
        for(int j = i + 1; j < hailStones.size(); j++){
            long double x1{hailStones[i][0]};
            long double x2{hailStones[i][2]};
            long double x3{hailStones[j][0]};
            long double x4{hailStones[j][2]};
            long double y1{hailStones[i][1]};
            long double y2{hailStones[i][3]};
            long double y3{hailStones[j][1]};
            long double y4{hailStones[j][3]};
            long double slope1{(y2 - y1) / (x2 - x1)};          // la pente de la droite
            long double bParameter1{y1 - x1 * slope1};          // b dans l'équation y = mx + b avec m représente la pente
            long double slope2{(y4 - y3) / (x4 - x3)};          // la pente de la droite
            long double bParameter2{y3 - x3 * slope2};          // b dans l'équation y = mx + b avec m représente la pente
            if(slope1 != slope2){                               // si les pentes sont identiques les droites sont parallèles
                double long intersectionPointX{(bParameter2 - bParameter1) / (slope1 - slope2)};        // point d'intersection des droites
                double long intersectionPointY{(slope1 * intersectionPointX + bParameter1)};            // point d'intersection des droites
                std::cout << "intersectionPointX: " << intersectionPointX << "\n";
                std::cout << "intersectionPointY: " << intersectionPointY << "\n";
                if(intersectionPointX >= MIN_INTERVAL && intersectionPointX <= MAX_INTERVAL && intersectionPointY >= MIN_INTERVAL && intersectionPointY <= MAX_INTERVAL){
                    long double vx1{hailStones[i][4]};
                    long double vy1{hailStones[i][5]};
                    long double vx2{hailStones[j][4]};
                    long double vy2{hailStones[j][5]};
                    bool hailStoneAInFuture{true};
                    bool hailStoneBInFuture{true};
                    if(intersectionPointX < x1 && vx1 > 0 || intersectionPointX > x1 && vx1 < 0 || intersectionPointY < y1 && vy1 > 0 || intersectionPointY > y1 && vy1 < 0){
                        hailStoneAInFuture = false;                     // si l'intersection a eu lieu dans le passé
                    }
                    if(intersectionPointX < x3 && vx2 > 0 || intersectionPointX > x3 && vx2 < 0 || intersectionPointY < y3 && vy2 > 0 || intersectionPointY > y3 && vy2 < 0){
                        hailStoneBInFuture = false;                     // si l'intersection a eu lieu dans le passé
                    }
                    if(hailStoneAInFuture && hailStoneBInFuture){
                        res++;
                    }
                }
            }
        }
    }
    std::cout << res << "\n";
    return 0;
}