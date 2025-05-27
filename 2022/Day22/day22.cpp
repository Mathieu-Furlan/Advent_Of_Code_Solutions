#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::vector<char>> matrix;
    std::string directions;
    std::array<char, 4> actualDir{'R', 'D', 'L', 'U'};
    while(getline(file, s)){
        if(s[0] > 47 && s[0] < 58){
            directions = s;
        }
        else if(s.length() > 0){
            std::vector<char> createRow;
            for(int i = 0; i <= s.length() - 1; i++){
                createRow.push_back(s[i]);
            }
            matrix.push_back(createRow);
        }
    }
    int actualRow{0};
    int actualCol;
    for(int i = 0; i <= matrix[0].size() - 1; i++){
        if(matrix[0][i] != ' '){
            actualCol = i;
            break;
        }
    }
    std::string value;
    int facing{0};
    for(int j = 0; j <= directions.length() - 1; j++){
        if(j < 20){
            std::cout << "row " << actualRow << "\n";
            std::cout << "col " << actualCol << "\n";
            std::cout << "facing " << facing << "\n";
            std::cout << "\n";
        }
        while(directions[j] > 47 && directions[j] < 58){
            value += directions[j];
            j++;
        }
        if(s[j] == 'R' || s[j] == 'L' || j == directions.length()){
            int movement{std::stoi(value)};
            value.clear();
            if(facing == 0){                            // si on se dirige vers la droite
                while(movement > 0){
                    if(actualCol < matrix[actualRow].size() - 1 && matrix[actualRow][actualCol + 1] == '#'){
                        break;
                    }
                    else if(actualCol == matrix[actualRow].size() - 1){
                        int index{0};
                        while(matrix[actualRow][index] == ' '){
                            index++;
                        }
                        if(matrix[actualRow][index] != '#'){
                            actualCol = index;
                        }
                        else break;
                    }
                    else actualCol++;
                    movement--;
                }
            }
            else if(facing == 2){                                   // si on se dirige vers la gauche
                while(movement > 0){
                    if(actualCol > 0 && matrix[actualRow][actualCol - 1] == '#'){
                        break;
                    }
                    else if(actualCol == 0 || matrix[actualRow][actualCol - 1] == ' '){
                        if(matrix[actualRow][matrix[actualRow].size() - 1] == '#'){
                            break;
                        }
                        else actualCol = matrix[actualRow].size() - 1;
                    }
                    else actualCol--;
                    movement--;
                }
            }
            else if(facing == 3){                                   // si on se dirige vers le haut
                while(movement > 0){
                    if(actualRow > 0 && matrix[actualRow - 1][actualCol] == '#'){
                        break;
                    }
                    else if(actualRow == 0 || matrix[actualRow - 1][actualCol] == ' '){
                        long unsigned index{matrix.size() - 1};
                        while(matrix[index].size() < actualCol + 1){
                            index--;
                        }
                        if(index == -1){
                            index = matrix.size() - 1;
                        }
                        std::cout << "index " << index << "\n";
                        while(actualCol > matrix[index].size() - 1 || matrix[index][actualCol] == ' '){
                            index--;
                            if(index == -1){
                                index = matrix.size() - 1;
                            }
                        }
                        if(matrix[index][actualCol] == '#'){
                            break;
                        }
                        else actualRow = index;
                    }
                    else actualRow--;
                    movement--;
                }
            }
            else if(facing == 1){                                   // si on se dirige vers le bas
                while(movement > 0){
                    if(actualRow < matrix.size() - 1 && matrix[actualRow + 1][actualCol] == '#'){      // dans le cas où on est immédiatement bloqué
                        break;
                    }
                    else if(actualRow == matrix.size() || actualCol >= matrix[actualRow + 1].size() || matrix[actualRow + 1][actualCol] == ' '){
                        int index{0};
                        while(actualCol >= matrix[index].size() || matrix[index][actualCol] == ' '){
                            index++;
                            if(index == matrix.size()){
                                index = 0;
                            }
                        }
                        if(matrix[index][actualCol] == '#'){
                            break;
                        }
                        else actualRow = index;
                    }
                    else actualRow++;
                    movement--;
                }
            }
            if(directions[j] == 'R'){
                facing++;
                if(facing == 4){
                    facing = 0;
                }
            }
            else if(directions[j] == 'L'){
                facing--;
                if(facing == -1){
                    facing = 3;
                }
            }
        }
    }
    std::cout << "row " << actualRow << "\n";
    std::cout << "col " << actualCol << "\n";
    std::cout << "facing " << facing << "\n";
    std::cout << 1000 * (actualRow + 1) + 4 * (actualCol + 1) + facing << "\n";
    return 0;
}