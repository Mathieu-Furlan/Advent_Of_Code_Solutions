#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    int currPos{0};
    int skipSize{0};
    std::array<int, 256> startList;
    for(int i = 0; i <= 255; i++){
        startList[i] = i;
    }
    getline(file, s);
    std::string lengthsBuilder;
    for(int i = 0; i <= s.length(); i++){
        if(s[i] == ',' || i == s.length()){    // si i = s.length() alors il s'agit du dernier élément de la ligne
            int currLength = std::stoi(lengthsBuilder);
            if(currLength <= 1){                // si il y a un élément ou moins il n'y a pas d'inversion
                lengthsBuilder.clear();
                std::cout << "currPos " << currPos << "\n";
                currPos = (skipSize + currPos + currLength) % 256;
                std::cout << "currPos " << currPos << "\n";
                skipSize++;
                continue;
            }
            lengthsBuilder.clear();
            int copyLength{currLength};
            std::vector<int> selectedElems;            // on place les éléments à inverser dans un vecteur
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
            for(int n = 0; n <= startList.size() - 1; n++){
                std::cout << startList[n] << " ";
            }
            std::cout << "endList" << "\n";
        }
        else lengthsBuilder += s[i];
    }
    std::cout << startList[0] * startList[1] << "\n";
    return startList[0] * startList[1];
}