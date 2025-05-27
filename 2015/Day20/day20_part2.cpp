#include <iostream>
#include <vector>

int main(){
    bool found{false};
    int houseNumber{2};
    while(!found){
        int sum{0};
        for(int i = 1; i <= 50; i++){
            if(houseNumber % i == 0){
                sum += houseNumber / i;
            }
        }
        sum *= 11;
        if(sum >= 34000000){
            std::cout << houseNumber << "\n";
            found = true;
        }
        houseNumber++;
    }
    return 0;
}