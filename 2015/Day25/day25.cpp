#include <iostream>

int main(){
    long startingValue{20151125};
    for(int i = 2; i <= 6028; i++){
        for(int j = 1; j <= i; j++){
            startingValue *= 252533;
            startingValue %= 33554393;
            if(i == 6028 && j == 3019){                     // 6028 = 3010 + 3019 - 1
                std::cout << startingValue << "\n";
                break;
            }
        }
    }
    return 0;
}