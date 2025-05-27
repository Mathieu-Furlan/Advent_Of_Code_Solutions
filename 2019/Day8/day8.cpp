#include <fstream>
#include <string>
#include <iostream>
#include <limits>

int main(){
    std::ifstream file("input");
    std::string s;
    int pixels{0};
    int fewestZeroes{std::numeric_limits<int>::max()};
    int zeroes{0};
    int ones{0};
    int twos{0};
    int res;
    while(getline(file, s)){
        for(int i = 0; i <= s.length() - 1; i++){
            pixels++;
            if(s[i] == '0'){
                zeroes++;
            }
            else if(s[i] == '1'){
                ones++;
            }
            else if(s[i] == '2'){
                twos++;
            }
            if(pixels == 150){
                if(zeroes < fewestZeroes){
                    res = ones * twos;
                    fewestZeroes = zeroes;
                }
                zeroes = 0;
                ones = 0;
                twos = 0;
                pixels = 0;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}