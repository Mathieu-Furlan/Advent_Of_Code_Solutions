#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<int> numsConsidered;
    int preamble{0};
    while(getline(file, s)){
        preamble++;
        if(preamble <= 25){
            numsConsidered.push_back(std::stoi(s));
        }
        else{
            int currentValue{std::stoi(s)};
            bool sumOfPrevious{false};
            for(int i = 0; i <= numsConsidered.size() - 2; i++){
                for(int j = i + 1; j <= numsConsidered.size() - 1; j++){
                    if(numsConsidered[i] + numsConsidered[j] == currentValue){
                        sumOfPrevious = true;
                    }
                }
            }
            if(!sumOfPrevious){
                std::cout << currentValue << "\n";
                break;
            }
            numsConsidered.erase(numsConsidered.begin());
            numsConsidered.push_back(currentValue);
        }
    }
    return 0;
}