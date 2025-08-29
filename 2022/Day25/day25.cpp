#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    long res{0};
    while(getline(file, s)){
        long powerFive{1};
        long snafuNumb{0};
        for(int i = s.length() - 1; i >= 0; i--){
            if(s[i] == '1'){
                snafuNumb += powerFive;
            }
            else if(s[i] == '2'){
                snafuNumb += powerFive * 2;
            }
            else if(s[i] == '-'){
                snafuNumb -= powerFive;
            }
            else if(s[i] == '='){
                snafuNumb -= powerFive * 2;
            }
            powerFive *= 5;
        }
        res += snafuNumb;
    }
    std::cout << res << "\n";
    std::string snafuRes;
    long startingPower{1};
    while(startingPower * 2 < res){
        startingPower *= 5;
    }
    while(startingPower > 1){
        if(res > startingPower){
            snafuRes += '2';
            res -= startingPower * 2;
            startingPower /= 5;
        }
        else if(res <= startingPower && res > 0){
            
        }
    }
    return res;
}