#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string grid;
    while(getline(file, s)){
        grid += s;
    }
    std::unordered_set<std::string> states{grid};
    while(true){
        std::string next;
        for(int i = 0; i < grid.length(); i++){
            int neighbours{0};
            if(grid[i] == '#'){
                if(i - 5 >= 0 && grid[i - 5] == '#'){              // au dessus
                    neighbours++;
                }
                if(i % 5 != 0 && grid[i - 1] == '#'){              // à gauche
                    neighbours++;
                }
                if(i + 5 < grid.length() && grid[i + 5] == '#'){      // en dessous
                    neighbours++;
                }
                if((i + 1) % 5 != 0 && grid[i + 1] == '#'){        // à droite
                    neighbours++;
                }
                if(neighbours != 1){
                    next += '.';
                }
                else next += '#';
            }
            else{
                if(i - 5 >= 0 && grid[i - 5] == '#'){              // au dessus
                    neighbours++;
                }
                if(i % 5 != 0 && grid[i - 1] == '#'){              // à gauche
                    neighbours++;
                }
                if(i + 5 < grid.length() && grid[i + 5] == '#'){      // en dessous
                    neighbours++;
                }
                if((i + 1) % 5 != 0 && grid[i + 1] == '#'){        // à droite
                    neighbours++;
                }
                if(neighbours == 1 || neighbours == 2){
                    next += '#';
                }
                else next += '.';
            }
        }
        grid = next;
        if(states.find(grid) != states.end()){
            break;
        }
        states.insert(grid);
    }
    unsigned long res{0};
    long powerOfTwo{1};
    for(int i = 0; i < grid.length(); i++){
        if(grid[i] == '#'){
            res += powerOfTwo;
        }
        powerOfTwo *= 2;
    }
    std::cout << res << "\n";
    return 0;
}