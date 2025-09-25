#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    getline(file, s);
    std::vector<int> currentRow;
    int safeTiles{0};
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '.'){
            safeTiles++;
            currentRow.push_back(0);
        }
        else currentRow.push_back(1);
    }
    int rows{1};
    while(rows < 400000){
        std::vector<int> nextRow;
        if(currentRow[1]){
            nextRow.push_back(1);
        }
        else{
            nextRow.push_back(0);
            safeTiles++;
        }
        for(int i = 1; i < currentRow.size() - 1; i++){
            if((currentRow[i - 1] && currentRow[i] && !currentRow[i + 1]) || (!currentRow[i - 1] && currentRow[i] && currentRow[i + 1]) || (currentRow[i - 1] && !currentRow[i] && !currentRow[i + 1]) || (!currentRow[i - 1] && !currentRow[i] && currentRow[i + 1])){
                nextRow.push_back(1);
            }
            else{
                nextRow.push_back(0);
                safeTiles++;
            }
        }
        if(currentRow[currentRow.size() - 2]){
            nextRow.push_back(1);
        }
        else{
            nextRow.push_back(0);
            safeTiles++;
        }
        currentRow = nextRow;
        rows++;
    }
    std::cout << safeTiles << "\n";
    return 0;
}