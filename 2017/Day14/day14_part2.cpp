#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ios>
#include <sstream>
#include <bitset>
#include <stack>

void visitRegion(std::vector<std::string>& rows, std::array<std::array<bool, 128>, 128>& visited, std::stack<std::array<int, 2>>& regions, std::array<int, 2> firstElem){
    std::stack<std::array<int, 2>> processIndividual;
    processIndividual.push(firstElem);
    while(processIndividual.size() > 0){
        std::array<int, 2> regionElem{processIndividual.top()};
        processIndividual.pop();
        if(regionElem[0] > 0 && !visited[regionElem[0] - 1][regionElem[1]]){
            if(rows[regionElem[0] - 1][regionElem[1]] == '1'){
                processIndividual.push({regionElem[0] - 1, regionElem[1]});
                visited[regionElem[0] - 1][regionElem[1]] = true;
            }
            else{
                regions.push({regionElem[0] - 1, regionElem[1]});
                visited[regionElem[0] - 1][regionElem[1]] = true;
            }
        }
        if(regionElem[0] < rows.size() - 1 && !visited[regionElem[0] + 1][regionElem[1]]){
            if(rows[regionElem[0] + 1][regionElem[1]] == '1'){
                processIndividual.push({regionElem[0] + 1, regionElem[1]});
                visited[regionElem[0] + 1][regionElem[1]] = true;
            }
            else{
                regions.push({regionElem[0] + 1, regionElem[1]});
                visited[regionElem[0] + 1][regionElem[1]] = true;
            }
        }
        if(regionElem[1] > 0 && !visited[regionElem[0]][regionElem[1] - 1]){
            if(rows[regionElem[0]][regionElem[1] - 1] == '1'){
                processIndividual.push({regionElem[0], regionElem[1] - 1});
                visited[regionElem[0]][regionElem[1] - 1] = true;
            }
            else{
                regions.push({regionElem[0], regionElem[1] - 1});
                visited[regionElem[0]][regionElem[1] - 1] = true;
            }
        }
        if(regionElem[1] < rows[0].length() - 1 && !visited[regionElem[0]][regionElem[1] + 1]){
            if(rows[regionElem[0]][regionElem[1] + 1] == '1'){
                processIndividual.push({regionElem[0], regionElem[1] + 1});
                visited[regionElem[0]][regionElem[1] + 1] = true;
            }
            else{
                regions.push({regionElem[0], regionElem[1] + 1});
                visited[regionElem[0]][regionElem[1] + 1] = true;
            }
        }
    }
}

int main(){
    std::vector<std::string> rows;
    std::array<std::array<bool, 128>, 128> visited;
    for(int i = 0; i <= 127; i++){
        std::string inputText{"hxtvlmkl-"};
        inputText += std::to_string(i);
        std::vector<int> lengths;
        for(int m = 0; m <= inputText.length() - 1; m++){
            lengths.push_back(inputText[m]);
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
        std::array<bool, 128> temp;
        std::fill(temp.begin(), temp.end(), false);
        visited[i] = temp;
        rows.push_back(binaryRow);
    }
    int res{0};
    std::stack<std::array<int, 2>> regions; 
    regions.push({0, 0});
    visited[0][0] = true;
    while(regions.size() > 0){
        std::array<int, 2> rowElem{regions.top()};
        regions.pop();
        if(rowElem[0] > 0 && !visited[rowElem[0] - 1][rowElem[1]]){
            if(rows[rowElem[0] - 1][rowElem[1]] == '0'){
                regions.push({rowElem[0] - 1, rowElem[1]});
                visited[rowElem[0] - 1][rowElem[1]] = true;
            }
            else{
                visitRegion(rows, visited, regions, {rowElem[0] - 1, rowElem[1]}); // on visite les éléments de la région immédiatement pour ne pas compter deux fois certains éléments
                visited[rowElem[0] - 1][rowElem[1]] = true;
                res++;
            }
        }
        if(rowElem[0] < rows.size() - 1 && !visited[rowElem[0] + 1][rowElem[1]]){
            if(rows[rowElem[0] + 1][rowElem[1]] == '0'){
                regions.push({rowElem[0] + 1, rowElem[1]});
                visited[rowElem[0] + 1][rowElem[1]] = true;
            }
            else{
                visitRegion(rows, visited, regions, {rowElem[0] + 1, rowElem[1]});
                visited[rowElem[0] + 1][rowElem[1]] = true;
                res++;
            }
        }
        if(rowElem[1] > 0 && !visited[rowElem[0]][rowElem[1] - 1]){
            if(rows[rowElem[0]][rowElem[1] - 1] == '0'){
                regions.push({rowElem[0], rowElem[1] - 1});
                visited[rowElem[0]][rowElem[1] - 1] = true;
            }
            else{
                visitRegion(rows, visited, regions, {rowElem[0], rowElem[1] - 1});
                visited[rowElem[0]][rowElem[1] - 1] = true;
                res++;
            }
        }
        if(rowElem[1] < rows[0].length() - 1 && !visited[rowElem[0]][rowElem[1] + 1]){
            if(rows[rowElem[0]][rowElem[1] + 1] == '0'){
                regions.push({rowElem[0], rowElem[1] + 1});
                visited[rowElem[0]][rowElem[1] + 1] = true;
            }
            else{
                visitRegion(rows, visited, regions, {rowElem[0], rowElem[1] + 1});
                visited[rowElem[0]][rowElem[1] + 1] = true;
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}