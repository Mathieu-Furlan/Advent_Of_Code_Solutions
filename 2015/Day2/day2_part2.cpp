#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <array>

int main(){
    std::ifstream infile("input");
    std::string s;
    int res{0};
    while(infile >> s){
        std::string lengthBox;
        std::string widthBox;
        std::string heightBox;
        int created{0};
        for(int i = 0; i <= s.length() - 1; i++){
            if(created == 0 && s[i] > 47 && s[i] < 58){
                lengthBox += s[i];
            }
            else if(created == 1 && s[i] > 47 && s[i] < 58){
                widthBox += s[i];
            }
            else if(created == 2 && s[i] > 47 && s[i] < 58){
                heightBox += s[i];
            }
            else if(s[i] == 'x'){
                created++;
            }
        }
        int lengthInt{stoi(lengthBox)};
        int widthInt{stoi(widthBox)};
        int heightInt{stoi(heightBox)};
        std::array<int, 3> boxDim{{lengthInt, widthInt, heightInt}};
        std::sort(boxDim.begin(), boxDim.end());
        res += 2 * boxDim[0] + 2 * boxDim[1];
        std::cout << boxDim[0] << "\n";
        res += lengthInt * widthInt * heightInt;
        std::cout << boxDim[1] << "\n";
    }
    std::cout << res << "\n";
    return res;
}