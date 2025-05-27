#include <fstream>
#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <cmath>
		

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        int maxLign{std::numeric_limits<int>::min()};
        int minLign{std::numeric_limits<int>::max()};
        std::string numberBuilder;
        std::vector<double> numberList;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58){
                numberBuilder += s[i];
            }
            else if(numberBuilder.length() > 0){
                double currNumber{std::stod(numberBuilder)};
                numberList.push_back(currNumber);
                numberBuilder.clear();
            }
        }
        double currNumber{std::stod(numberBuilder)};
        numberList.push_back(currNumber);
        std::sort(numberList.begin(), numberList.end());
        bool foundRes{false};
        for(int j = numberList.size() - 1; j >= 0; j--){
            for(int k = j - 1; k >= 0; k--){
                double intChecker{numberList[j] / numberList[k]};
                if(std::floor(intChecker) == intChecker){
                    std::cout << "j " << numberList[j] << "\n";
                    std::cout << "k " << numberList[k] << "\n";
                    res += numberList[j] / numberList[k];
                    foundRes = true;
                    break;
                }
            }
            if(foundRes){
                break;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}