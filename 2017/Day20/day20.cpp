#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <array>
#include <limits>

int main(){                          // on recherche la plus forte acceleration
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<int, 3>> particules;
    std::array<int, 3> caracteristics;
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
                caracteristics[countVal] = std::stoi(valueBuilder);
                valueBuilder.clear();
                countVal++;
                if(countVal == 3){
                    particules.push_back(caracteristics);
                    countVal = 0;
                }
            }
        }
    }
    int res;
    int slowestAcceleration{std::numeric_limits<int>::max()};
    int startingVelocity{std::numeric_limits<int>::max()};
    int particuleNumber{0};
    for(int i = 2; i <= particules.size() - 1; i = i + 3){
        int totalAcceleration{0};
        int veloce{0};
        for(int j = 0; j <= 2; j++){
            if(particules[i][j] < 0){
                totalAcceleration += particules[i][j] * -1;
            }
            else totalAcceleration += particules[i][j];
        }
        for(int j = 0; j <= 2; j++){                // si deux accelerations sont égales, ont compare les vélocités de départ
            if(particules[i - 1][j] < 0){
                if(particules[i][j] < 0){
                    veloce += particules[i - 1][j] * -1;
                }
                else veloce += particules[i - 1][j];
            }
            else{
                if(particules[i][j] < 0){
                    veloce -= particules[i - 1][j];
                }
                else veloce += particules[i - 1][j];
            }
        }
        if(totalAcceleration < slowestAcceleration){
            slowestAcceleration = totalAcceleration;
            startingVelocity = veloce;
            res = particuleNumber;
        }
        else if(totalAcceleration == slowestAcceleration){
            if(veloce < startingVelocity){
                startingVelocity = veloce;
            }
            res = particuleNumber;
        }
        particuleNumber++;
    }
    std::cout << res << "\n";
    return res;
}