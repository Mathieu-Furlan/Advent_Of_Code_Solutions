#include <fstream>
#include <string>
#include <iostream>
#include <limits>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        int maxLign{std::numeric_limits<int>::min()};
        int minLign{std::numeric_limits<int>::max()};
        std::string numberBuilder;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58){
                numberBuilder += s[i];
            }
            else if(numberBuilder.length() > 0){
                int currNumber = std::stoi(numberBuilder);
                if(currNumber < minLign){
                    minLign = currNumber;
                }
                if(currNumber > maxLign){
                    maxLign = currNumber;
                }
                numberBuilder.clear();
            }
        }
        int currNumber = std::stoi(numberBuilder);
        if(currNumber < minLign){
            minLign = currNumber;
        }
        if(currNumber > maxLign){
            maxLign = currNumber;
        }
        res += maxLign - minLign;
    }
    std::cout << res << "\n";
    return res;
}