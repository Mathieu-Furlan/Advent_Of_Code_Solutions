#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    int rows{0};
    std::unordered_map<int, std::unordered_set<int>> matrix;
    while(getline(file, s)){
        for(int i = 0; i <= s.length() - 1; i++){
            if(matrix.find(i) == matrix.end()){
                std::unordered_set<int> init{rows};
                matrix.insert(std::make_pair(i, init));
            }
            else matrix.at(i).insert(rows);
        }
    }
    int res{0};
    for(auto& [key, value] : matrix){
        for(auto& asteroid : value){
            std::vector<std::array<int, 2>> detected;
            int visible{0};
            for(auto& [key, value] : matrix){
                for(auto& asteroid : value){
                if(detected.size() == 0){
                    detected.push_back({key, asteroid});
                    visible++;
                }
                else{
                    bool hidden{false};
                    for(auto& detect : detected){
                        if(key < detect[0]){
                            if(asteroid < detect[1]){
                                if(detect[0] % key == 0 && detect[1] % asteroid == 0){
                                    hidden = true;
                                    break;
                                }
                            }
                            else{
                                if(detect[0] % key == 0 && asteroid % detect[1] == 0){
                                    hidden = true;
                                    break;
                                }
                            }
                        }
                        else{
                            if(asteroid < detect[1]){
                                if(key % detect[0] == 0 && detect[1] % asteroid == 0){
                                    hidden = true;
                                    break;
                                }
                            }
                            else{
                                if(key % detect[0] == 0 && asteroid % detect[1] == 0){
                                    hidden = true;
                                    break;
                                }
                            }
                        }
                        if(hidden){
                            break;
                        }
                    }
                if(!hidden){
                    detected.push_back({key, asteroid});
                    visible++;
                }
            }
        }
    }
}