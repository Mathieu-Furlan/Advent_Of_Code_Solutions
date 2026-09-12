#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string startingPoint;
    std::vector<std::string> grid;
    while(getline(file, s)){
        startingPoint += s;
    }
    grid.push_back(startingPoint);
    grid[0][12] = '?';
    int minutes = 200;
    while(minutes > 0){
        if(minutes > 189){
            for(int i = 0; i < grid.size(); i++){
                for(int j = 0; j < grid[i].length(); j++){
                    std::cout << grid[i][j];
                }
                std::cout << "\n";
            }
            std::cout << "end" << "\n";
        }
        minutes--;
        std::vector<std::string> next;
        grid.insert(grid.begin(), "............?............");
        grid.push_back("............?............");
        next.push_back("............?............");
        for(int i = 0; i < grid.size(); i++){
            next.push_back("............?............");
            for(int j = 0; j < grid[i].length(); j++){
                int neighbours{0};
                if(grid[i][j] != '?'){
                    if(i < grid.size() - 1){
                        if(j >= 0 && j <= 4){               // niveau supérieur au dessus
                            if(grid[i + 1][7] == '#'){
                                neighbours++;
                            }
                        }
                        if(j % 5 == 0){                     // niveau supérieur à gauche
                            if(grid[i + 1][11] == '#'){
                                neighbours++;
                            }
                        }
                        if(j >= 20){                        // niveau supérieur en dessous
                            if(grid[i + 1][17] == '#'){
                                neighbours++;
                            }
                        }
                        if(j == 4 || j == 9 || j == 14 || j == 19 || j == 24){              // niveau supérieur à droite
                            if(grid[i + 1][13] == '#'){
                                neighbours++;
                            }
                        }
                    }
                    if(i > 0){
                        if(j == 7){                                 // niveau inférieur au dessus
                            for(int k = 0; k < 5; k++){
                                if(grid[i - 1][k] == '#'){
                                    neighbours++;
                                }
                            }
                        }
                        if(j == 11){                                // niveau inférieur à gauche
                            for(int k = 0; k < 25; k = k + 5){
                                if(grid[i - 1][k] == '#'){
                                    neighbours++;
                                }
                            }
                        }
                        if(j == 13){                                // niveau inférieur à droite
                            for(int k = 4; k < 25; k = k + 5){
                                if(grid[i - 1][k] == '#'){
                                    neighbours++;
                                }
                            }
                        }
                        if(j == 17){                                // niveau inférieur en dessous
                            for(int k = 20; k < 25; k++){
                                if(grid[i - 1][k] == '#'){
                                    neighbours++;
                                }
                            }
                        }
                    }
                    if(j - 5 >= 0 && grid[i][j - 5] == '#'){              // au dessus
                        neighbours++;
                    }
                    if(j % 5 != 0 && grid[i][j - 1] == '#'){              // à gauche
                        neighbours++;
                    }
                    if(j + 5 < grid[i].length() && grid[i][j + 5] == '#'){      // en dessous
                        neighbours++;
                    }
                    if((j + 1) % 5 != 0 && grid[i][j + 1] == '#'){        // à droite
                        neighbours++;
                    }
                    if(grid[i][j] == '#'){
                        if(neighbours != 1){
                            next[i][j] = '.';
                        }
                        else next[i][j] = '#';
                    }
                    else{
                        if(neighbours == 1 || neighbours == 2){
                            next[i][j] = '#';
                        }
                        else next[i][j] = '.';
                    }
                }
            }
        }
        next.push_back("............?............");
        grid = next;
    }
    unsigned long res{0};
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].length(); j++){
            if(grid[i][j] == '#'){
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return 0;
}