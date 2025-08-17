#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <limits>

int main(){
    std::ifstream file("input");
    std::string s;
    std::array<std::array<int, 26>, 8> freqs;
    for(int i = 0; i < 8; i++){
        std::fill(freqs[i].begin(), freqs[i].end(), 0);
    }
    while(getline(file, s)){
        for(int i = 0; i < 8; i++){
            freqs[i][s[i] - 97]++;
        }
    }
    std::string message;
    for(int i = 0; i < 8; i++){
        char letter;
        int minFreq{std::numeric_limits<int>::max()};
        for(int j = 0; j < 26; j++){
            if(freqs[i][j] < minFreq){
                letter = j + 97;
                minFreq = freqs[i][j];
            }
        }
        message += letter;
    }    
    std::cout << message << "\n";
    return 0;
}