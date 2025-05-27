#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ios>
#include <sstream>
#include <bitset>

int main(){
    int res{0};
    for(int i = 0; i <= 127; i++){
        std::string inputText{"hxtvlmkl-"};
        inputText += std::to_string(i);
        std::vector<int> lengths;
        for(int m = 0; m <= inputText.length() - 1; m++){
            lengths.push_back(inputText[m]);
        }
        lengths.push_back(17);         // il faut toujours ajouter les nombres donnés le dixième jour
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
                binaryXOR = binaryXOR ^ startList[n];
            }
            bitwiseXOR[indexXOR] = binaryXOR;
            indexXOR++;
        }
        std::string binaryRow;
        for(int n = 0; n <= bitwiseXOR.size() - 1; n++){
            std::stringstream ss;
            ss << std::hex << bitwiseXOR[n];
            std::string hexRepresentation;
            ss >> hexRepresentation;
            if(hexRepresentation.length() == 1){
                hexRepresentation = '0' + hexRepresentation;
            }
            for(int p = 0; p < 2; p++){
                if(hexRepresentation[p] > 47 && hexRepresentation[p] < 58){
                    std::bitset<4> binaryRepresentation(hexRepresentation[p] - '0');
                    binaryRow += binaryRepresentation.to_string();
                }
                else{
                    std::bitset<4> binaryRepresentation(hexRepresentation[p] - 87);
                    binaryRow += binaryRepresentation.to_string();
                }
                
            }
        }
        for(int i = 0; i <= binaryRow.length() - 1; i++){
            if(binaryRow[i] == '1'){
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}