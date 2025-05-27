#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<int, std::array<int, 3>> positions;
    std::unordered_map<int, std::array<int, 3>> velocities;
    std::unordered_map<int, std::array<int, 3>> accelerations;
    std::array<int, 3> caracteristics;
    int particleNumber{0};
    while(getline(file, s)){
        int countVal{0};
        std::string valueBuilder;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == '-' || s[i] > 47 && s[i] < 58){
                valueBuilder += s[i];
                int index{i + 1};
                while(s[index] > 47 && s[index] < 58){
                    valueBuilder += s[index];
                    index++;
                    i++;
                }
                caracteristics[countVal % 3] = std::stoi(valueBuilder);
                valueBuilder.clear();
                countVal++;
                if(countVal % 3 == 0){
                    if(countVal == 3){
                        positions.insert(std::make_pair(particleNumber, caracteristics));
                    }
                    else if(countVal == 6){
                        velocities.insert(std::make_pair(particleNumber, caracteristics));
                    }
                    else accelerations.insert(std::make_pair(particleNumber, caracteristics));
                }
            }
        }
        particleNumber++;
    }
    int ticks{0};
    while(positions.size() > 0 && ticks < 500){         // 500 choisi arbitrairement
        for(auto& [key, value] : accelerations){
            velocities.at(key)[0] += value[0];
            velocities.at(key)[1] += value[1];
            velocities.at(key)[2] += value[2];
        }
        for(auto& [key, value] : velocities){
            positions.at(key)[0] += value[0];
            positions.at(key)[1] += value[1];
            positions.at(key)[2] += value[2];
        }
        std::vector<int> toBeErased;
        for(int i = 0; i <= particleNumber - 2; i++){       // on vérifie que l'élément est toujours présent et on compare les positions
            for(int j = i + 1; j <= particleNumber - 1; j++){
                if(positions.find(i) != positions.end() && positions.find(j) != positions.end() && positions.at(i)[0] == positions.at(j)[0] && positions.at(i)[1] == positions.at(j)[1] && positions.at(i)[2] == positions.at(j)[2]){
                    toBeErased.push_back(i);
                    toBeErased.push_back(j);
                }
            }
        }
        for(auto& destroyed : toBeErased){
            positions.erase(destroyed);
            velocities.erase(destroyed);
            accelerations.erase(destroyed);
        }
        ticks++;
    }
    std::cout << positions.size() << "\n";
    return 0;
}