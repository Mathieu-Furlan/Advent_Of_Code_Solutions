#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_set<std::string> visited;
    bool found{false};
    getline(file, s);
    int horizontal{0};
    int vertical{0};
    int facingDir{0};                               // 0 nord, 3 est, 6 sud, 9 ouest
    for(int i = 0; i < s.length(); i++){
        if(s[i] == 'R'){
            std::string number;
            i++;
            while(s[i] >= 48 && s[i] <= 57){
                number += s[i];
                i++;
            }
            int blocks{std::stoi(number)};
            if(facingDir == 0){
                while(blocks > 0){
                    blocks--;
                    horizontal++;
                    std::string coordinates{std::to_string(horizontal) + ',' + std::to_string(vertical)};
                    if(std::find(visited.begin(), visited.end(), coordinates) != visited.end()){
                        found = true;
                        break;
                    }
                    visited.insert(coordinates);
                }
                facingDir = 3;
            }
            else if(facingDir == 3){
                while(blocks > 0){
                    blocks--;
                    vertical--;
                    std::string coordinates{std::to_string(horizontal) + ',' + std::to_string(vertical)};
                    if(std::find(visited.begin(), visited.end(), coordinates) != visited.end()){
                        found = true;
                        break;
                    }
                    visited.insert(coordinates);
                }
                facingDir = 6;
            }
            else if(facingDir == 6){
                while(blocks > 0){
                    blocks--;
                    horizontal--;
                    std::string coordinates{std::to_string(horizontal) + ',' + std::to_string(vertical)};
                    if(std::find(visited.begin(), visited.end(), coordinates) != visited.end()){
                        found = true;
                        break;
                    }
                    visited.insert(coordinates);
                }
                facingDir = 9;
            }
            else if(facingDir == 9){
                while(blocks > 0){
                    blocks--;
                    vertical++;
                    std::string coordinates{std::to_string(horizontal) + ',' + std::to_string(vertical)};
                    if(std::find(visited.begin(), visited.end(), coordinates) != visited.end()){
                        found = true;
                        break;
                    }
                    visited.insert(coordinates);
                }
                facingDir = 0;
            }
        }
        else if(s[i] == 'L'){
            std::string number;
            i++;
            while(s[i] >= 48 && s[i] <= 57){
                number += s[i];
                i++;
            }
            int blocks{std::stoi(number)};
            if(facingDir == 0){
                while(blocks > 0){
                    blocks--;
                    horizontal--;
                    std::string coordinates{std::to_string(horizontal) + ',' + std::to_string(vertical)};
                    if(std::find(visited.begin(), visited.end(), coordinates) != visited.end()){
                        found = true;
                        break;
                    }
                    visited.insert(coordinates);
                }
                facingDir = 9;
            }
            else if(facingDir == 3){
                while(blocks > 0){
                    blocks--;
                    vertical++;
                    std::string coordinates{std::to_string(horizontal) + ',' + std::to_string(vertical)};
                    if(std::find(visited.begin(), visited.end(), coordinates) != visited.end()){
                        found = true;
                        break;
                    }
                    visited.insert(coordinates);
                }
                facingDir = 0;
            }
            else if(facingDir == 6){
                while(blocks > 0){
                    blocks--;
                    horizontal++;
                    std::string coordinates{std::to_string(horizontal) + ',' + std::to_string(vertical)};
                    if(std::find(visited.begin(), visited.end(), coordinates) != visited.end()){
                        found = true;
                        break;
                    }
                    visited.insert(coordinates);
                }
                facingDir = 3;
            }
            else if(facingDir == 9){
                while(blocks > 0){
                    blocks--;
                    vertical--;
                    std::string coordinates{std::to_string(horizontal) + ',' + std::to_string(vertical)};
                    if(std::find(visited.begin(), visited.end(), coordinates) != visited.end()){
                        found = true;
                        break;
                    }
                    visited.insert(coordinates);
                }
                facingDir = 6;
            }
        }
        if(found){
            break;
        }
    }
    int res{std::abs(horizontal) + std::abs(vertical)};
    std::cout << res << "\n";
    return 0;
}