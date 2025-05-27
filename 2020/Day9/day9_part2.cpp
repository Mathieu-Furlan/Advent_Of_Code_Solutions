#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    const int PREV_RES{41682220};
    std::ifstream file("input");
    std::string s;
    std::vector<long> numbers;
    int preamble{0};
    while(getline(file, s)){
        numbers.push_back(std::stol(s));
    }
    for(int i = 0; i <= numbers.size() - 1; i++){
        int sum{0};
        for(int j = i; j <= numbers.size() - 1; j++){
            sum += numbers[j];
            if(sum == PREV_RES){
                int maxNumber{0};
                int minNumber{41682220};
                for(int k = i; k <= j; k++){
                    if(numbers[k] > maxNumber){
                        maxNumber = numbers[k];
                    }
                    if(numbers[k] < minNumber){
                        minNumber = numbers[k];
                    }
                }
                std::cout << minNumber + maxNumber << "\n";
                return 0;
            }
            else if(sum > PREV_RES){
                break;
            }
        }
    }
    return 0;
}