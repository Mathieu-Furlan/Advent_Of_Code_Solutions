#include <string>
#include <iostream>

int main(){
    std::string puzzleInput{"3113322113"};
    std::string res;
    for(int i = 0; i < 40; i++){
        long unsigned iterateOver{puzzleInput.length() - 1};
        for(int j = 0; j <= iterateOver; j++){
            int index{j + 1};
            int countSimilar{1};
            while(puzzleInput[index] == puzzleInput[j]){
                countSimilar++;
                j++;
                index++;
            }
            res += std::to_string(countSimilar);
            res += puzzleInput[j];
        }
        puzzleInput = res;
        res.clear();
    }
    std::cout << puzzleInput.length() << "\n";
    return 0;
}