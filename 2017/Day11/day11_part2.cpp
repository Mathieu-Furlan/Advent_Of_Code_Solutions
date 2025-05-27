#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    double verticalDistance{0};
    double horizontalDistance{0};
    int furthest{0};
    while(getline(file, s)){
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == 's'){
                if(s[i + 1] == ','){
                    verticalDistance--;
                }
                else if(s[i + 1] == 'e'){
                    verticalDistance -= 0.5;
                    horizontalDistance += 0.5;
                }
                else if(s[i + 1] == 'w'){
                    verticalDistance -= 0.5;
                    horizontalDistance -= 0.5;
                }
            }
            else if(s[i] == 'n'){
                if(s[i + 1] == ','){
                    verticalDistance++;
                }
                else if(s[i + 1] == 'e'){
                    verticalDistance += 0.5;
                    horizontalDistance += 0.5;
                }
                else if(s[i + 1] == 'w'){
                    verticalDistance += 0.5;
                    horizontalDistance -= 0.5;
                }
            }
            if(s[i] == 'n' || s[i] == 's'){
                double dist;
                double absoluteVertical = std::abs(verticalDistance);       // valeurs absolues car la direction n'a pas d'importance
                double absoluteHorizontal = std::abs(horizontalDistance);
                if(absoluteVertical >= absoluteHorizontal){
                    dist = absoluteHorizontal;
                    absoluteVertical -= absoluteHorizontal;
                    dist *= 2;
                    dist += absoluteVertical;
                }
                else{
                    dist = absoluteVertical;
                    absoluteHorizontal -= absoluteVertical;
                    dist *= 2;
                    dist += (absoluteHorizontal * 2);
                }
                if(dist > furthest){
                    furthest = dist;
                }
            }
        }
    }
    std::cout << furthest << "\n";
    return 0;
}