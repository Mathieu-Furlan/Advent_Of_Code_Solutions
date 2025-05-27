#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ios>

int main(){
    char ch;
    std::vector<int> lengths;
    std::fstream fin("input", std::fstream::in);
    while(fin >> std::noskipws >> ch){
        if(ch > 31){                    // pour ne pas tenir compte du symbole fin de ligne
            lengths.push_back(ch);
        }
    }
    lengths.push_back(17);
    lengths.push_back(31);
    lengths.push_back(73);
    lengths.push_back(47);
    lengths.push_back(23);
    int currPos{0};
    int skipSize{0};
    std::array<int, 256> startList;
    for(int i = 0; i <= 255; i++){
        startList[i] = i;
    }
    for(int j = 0; j < 64; j++){
        for(int k = 0; k <= lengths.size() - 1; k++){
            int currLength = lengths[k];
            if(currLength <= 1){
                currPos = (skipSize + currPos + currLength) % 256;
                skipSize++;
                continue;
            }
            int copyLength{currLength};
            std::vector<int> selectedElems;
            for(int j = currPos;; j = (j + 1) % 256){
                selectedElems.push_back(startList[j]);
                copyLength--;
                if(copyLength == 0){
                    break;
                }
            }
            std::reverse(selectedElems.begin(), selectedElems.end());
            int vectorSelector{0};
            for(int k = currPos;; k = (k + 1) % 256){
                startList[k] = selectedElems[vectorSelector];
                vectorSelector++;
                if(vectorSelector == selectedElems.size()){
                    break;
                }
            }
            int moveCurrPos{currLength + skipSize};
            while(moveCurrPos > 0){
                currPos++;
                moveCurrPos--;
                if(currPos == 256){
                    currPos = 0;
                }
            }
            skipSize++;
        }
    }
    std::array<int, 16> bitwiseXOR;
    int indexXOR{0};
    for(int m = 0; m < 256; m = m + 16){
        int binaryXOR{startList[m]};
        for(int n = m + 1; n < m + 16; n++){
            binaryXOR = binaryXOR ^ startList[n];     // ^ est le symbole du Xor numérique binaire
        }
        bitwiseXOR[indexXOR] = binaryXOR;
        indexXOR++;
    }
    for(int n = 0; n <= bitwiseXOR.size() - 1; n++){
        std::cout << std::hex << bitwiseXOR[n];            // il faut ajouter un zéro devant lorsqu'il n'y a qu'un seul caractère
        std::cout << "\n";
    }
    return 0;
}