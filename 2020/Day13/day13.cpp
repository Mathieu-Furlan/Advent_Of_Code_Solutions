#include <iostream>
#include <array>

int main(){
    std::array<int, 9> busIDs{13, 41, 467, 19, 17, 29, 353, 37, 23};
    int earliestDep{1008713};
    int waitingTime{earliestDep};
    int res;
    for(int i = 0; i <= 8; i++){
        int temp{busIDs[i]};
        while(temp < earliestDep){
            temp += busIDs[i];
        }
        if(temp - earliestDep < waitingTime){
            waitingTime = temp - earliestDep;
            res = waitingTime * busIDs[i];
        }
    }
    std::cout << res << "\n";
    return 0;
}