#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    int row{0};
    int col{0};
    int wayPointRow{1};
    int wayPointCol{10};
    while(getline(file, s)){
        std::string value;
        for(int i = 1; i <= s.length() - 1; i++){
            value += s[i];
        }
        int move{std::stoi(value)};             // nord et est sont positifs, sud et ouest négatifs
        if(s[0] == 'N'){
            wayPointRow += move;
        }
        else if(s[0] == 'S'){
            wayPointRow -= move;
        }
        else if(s[0] == 'E'){
            wayPointCol += move;
        }
        else if(s[0] == 'W'){
            wayPointCol -= move;
        }
        else if(s[0] == 'L'){
            for(int i = 1; i <= move / 90; i++){
                int temp{wayPointCol};
                wayPointCol = wayPointRow * -1;     // colonne égal ligne * -1
                wayPointRow = temp;                 // ligne égal précédente colonne
            }
        }
        else if(s[0] == 'R'){
            for(int i = 1; i <= move / 90; i++){
                int temp{wayPointRow};
                wayPointRow = wayPointCol * -1;     // ligne égal colonne * -1
                wayPointCol = temp;                 // colonne égal précédente ligne
            }
        }
        else if(s[0] == 'F'){
            col += move * wayPointCol;
            row += move * wayPointRow;
        }
        std::cout << "wayPointRow " << wayPointRow << "\n";
        std::cout << "wayPointCol " << wayPointCol << "\n";
        std::cout << row << "\n";
        std::cout << col << "\n";
    }
    int res{0};
    if(row < 0){
        row *= -1;
    }
    if(col < 0){
        col *= -1;
    }
    res += row + col;
    std::cout << res << "\n";
    return 0;
}