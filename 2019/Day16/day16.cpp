#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<int> sequence;
    std::array<int, 4> pattern{0, 1, 0, -1};
    getline(file, s);
    for(int i = 0; i < s.length(); i++){
        sequence.push_back(s[i] - 48);
    }
    int phase{0};
    while(phase < 100){
        int index{1};                           // 1 pour le premier décalage
        bool offSet{false};
        std::vector<int> next;
        for(int i = 0; i < sequence.size(); i++){
            int rowSum{0};
            int repetitions{i};
            if(offSet){
                repetitions--;
            }
            for(int j = 0; j < sequence.size(); j++){
                rowSum += sequence[j] * pattern[index];
                if(repetitions > 0){
                    repetitions--;
                }
                else{
                    index = (index + 1) % 4;
                    repetitions = i;
                }
            }
            rowSum = std::abs(rowSum);
            while(rowSum >= 10){
                rowSum %= 10;
            }
            next.push_back(rowSum);
            index = 0;
            offSet = true;                  // le décalage du tableau pattern après le premier décalage
        }
        sequence = next;
        phase++;
    }
    for(int i = 0; i < 8; i++){
        std::cout << sequence[i];
    }
    std::cout << "\n";
    return 0;
}