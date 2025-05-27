#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{1};
    int lines{0};
    int time{0};
    long long distance{0};
    while(getline(file, s)){
        if(lines == 0){
            std::string temp;
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] <= 57 && s[i] >= 48){
                    temp.push_back(s[i]);
                }
            }
            time = stoi(temp);
            lines++;
        }
        else{
            std::string temp;
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] <= 57 && s[i] >= 48){
                    temp.push_back(s[i]);
                }
            }
            distance = stoll(temp);
        }
    }
    int minimalTime{0};
    int left{0};
    int right{time};
    while(left <= right){                                  // binary search pour la valeur minimale
        double mid{std::floor((left + right) / 2)};
        if((time - mid) * mid > distance){
            right = mid - 1;
        }
        else if((time - mid) * mid < distance){
            left = mid + 1;
        }
        else if((time - mid) * mid == distance){
            minimalTime = mid + 1;
        }
    }
    std::cout << std::fixed << "left " << left << "\n";
    std::cout << std::fixed << "right " << right << "\n";
    if(minimalTime == 0){                       // s'il n'est pas possible d'obtenir une valeur exactement équivalente à distance alors left est la valeur minimale
        minimalTime = left;
    }
    int maximalTime{0};
    left = 0;
    right = time;
    while(left <= right){                                         // binary search pour la valeur maximale
        double mid{std::floor((left + right) / 2)};
        if((time - mid) * mid > distance){
            left = mid + 1;
        }
        else if((time - mid) * mid < distance){
            right = mid - 1;
        }
        else if((time - mid) * mid == distance){
            maximalTime = mid - 1;
        }
    }
    std::cout << std::fixed << "left " << left << "\n";
    std::cout << std::fixed << "right " << right << "\n";
    if(maximalTime == 0){
        maximalTime = right + 1;                           // + 1 pour inclure la valeur maximale
    }
    std::cout << maximalTime - minimalTime << "\n";
    return maximalTime - minimalTime;
}