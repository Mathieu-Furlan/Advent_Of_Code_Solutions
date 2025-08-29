#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>
#include <cmath>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::array<std::array<int, 2>, 10> ropeKnots;
    for(int i = 0; i < 10; i++){
        std::array<int, 2> init{0, 0};
        ropeKnots[i] = init;
    }
    std::unordered_set<std::string> visited{"0 0"};
    while(getline(file, s)){
        std::cout << "newLine" << "\n";
        std::string moves{s[2]};
        if(s.length() == 4){
            moves += s[3];
        }
        int movements{std::stoi(moves)};
        while(movements > 0){
            if(s[0] == 'L'){
                ropeKnots[0][1]--;
            }
            else if(s[0] == 'R'){
                ropeKnots[0][1]++;
            }
            else if(s[0] == 'U'){
                ropeKnots[0][0]++;
            }
            else if(s[0] == 'D'){
                ropeKnots[0][0]--;
            }
            std::cout << 0 << ": " << ropeKnots[0][0] << ' ' << ropeKnots[0][1] << "\n";
            for(int i = 1; i < 10; i++){
                if(ropeKnots[i][0] == ropeKnots[i - 1][0] && std::abs(ropeKnots[i][1] - ropeKnots[i - 1][1]) > 1){         // si le noeud est trop éloigné en bas ou en haut
                    if(ropeKnots[i][1] < ropeKnots[i - 1][1]){                      // si trop éloigné en bas
                        ropeKnots[i][1]++;
                    }
                    else ropeKnots[i][1]--;                                         // si trop éloigné en haut
                }
                else if(ropeKnots[i][1] == ropeKnots[i - 1][1] && std::abs(ropeKnots[i][0] - ropeKnots[i - 1][0]) > 1){     // si le noeud est trop éloigné à droite ou à gauche
                    if(ropeKnots[i][0] < ropeKnots[i - 1][0]){
                        ropeKnots[i][0]++;
                    }
                    else ropeKnots[i][0]--;
                }
                else if(std::abs(ropeKnots[i][0] - ropeKnots[i - 1][0]) + std::abs(ropeKnots[i][1] - ropeKnots[i - 1][1]) > 2){     // si le noeud est trop éloigné en diagonale
                    if(ropeKnots[i][0] < ropeKnots[i - 1][0] && ropeKnots[i][1] < ropeKnots[i - 1][1]){
                        ropeKnots[i][0]++;
                        ropeKnots[i][1]++;
                    }
                    else if(ropeKnots[i][0] < ropeKnots[i - 1][0] && ropeKnots[i][1] > ropeKnots[i - 1][1]){
                        ropeKnots[i][0]++;
                        ropeKnots[i][1]--;
                    }
                    else if(ropeKnots[i][0] > ropeKnots[i - 1][0] && ropeKnots[i][1] > ropeKnots[i - 1][1]){
                        ropeKnots[i][0]--;
                        ropeKnots[i][1]--;
                    }
                    else{
                        ropeKnots[i][0]--;
                        ropeKnots[i][1]++;
                    }
                }
                std::cout << i << ": " << ropeKnots[i][0] << ' ' << ropeKnots[i][1] << "\n";
            }
            visited.insert(std::to_string(ropeKnots[9][1]).append(' ' + std::to_string(ropeKnots[9][0])));
            movements--;
        }   
    }
    unsigned long res{visited.size()};
    std::cout << res << "\n";
    return 0;
}