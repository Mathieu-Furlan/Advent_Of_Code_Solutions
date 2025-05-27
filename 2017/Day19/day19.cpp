#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <unordered_map>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<int, std::unordered_map<int, char>> diagram;
    std::array<int, 2> currPos;
    char direction{'d'};
    int lignNumber{0};
    while(getline(file, s)){
        std::unordered_map<int, char> rowPopulation;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 32){
                rowPopulation.insert(std::make_pair(i, s[i]));
            }
        }
        diagram.insert(std::make_pair(lignNumber, rowPopulation));
        lignNumber++;
    }
    bool finish{false};
    std::string res;
    for(auto& [key, value] : diagram.at(0)){
        currPos = {0, key};
        while(!finish){
            std::cout << "currPos 0 " << currPos[0] << "\n";
            std::cout << "currPos 1 " << currPos[1] << "\n";
            if(diagram.find(currPos[0]) == diagram.end()){      // si on ne trouve pas la ligne
                finish = true;
            }
            else if(diagram.at(currPos[0]).find(currPos[1]) == diagram.at(currPos[0]).end()){   // si on ne trouve pas la colonne
                finish = true;
            }
            else if(diagram.at(currPos[0]).at(currPos[1]) == '|'){
                if(direction == 'd'){
                    currPos[0]++;
                }
                else if(direction == 'u'){
                    currPos[0]--;
                }
                else if(direction == 'r'){
                    currPos[1]++;
                }
                else if(direction == 'l'){
                    currPos[1]--;
                }
            }
            else if(diagram.at(currPos[0]).at(currPos[1]) == '-'){
                if(direction == 'l'){
                    currPos[1]--;
                }
                else if(direction == 'r'){
                    currPos[1]++;
                }
                else if(direction == 'u'){
                    currPos[0]--;
                }
                else if(direction == 'd'){
                    currPos[0]++;
                }
            }
            else if(diagram.at(currPos[0]).at(currPos[1]) == '+'){  // on vérifie la direction d'arrivée pour ne pas repartir dans le même sens
                if(direction != 'u' && diagram.find(currPos[0] + 1) != diagram.end() && diagram.at(currPos[0] + 1).find(currPos[1]) != diagram.at(currPos[0] + 1).end()){
                    currPos[0]++;
                    direction = 'd';
                }
                else if(direction != 'd' && diagram.find(currPos[0] - 1) != diagram.end() && diagram.at(currPos[0] - 1).find(currPos[1]) != diagram.at(currPos[0] - 1).end()){
                    currPos[0]--;
                    direction = 'u';
                }
                else if(direction != 'r' && diagram.at(currPos[0]).find(currPos[1] - 1) != diagram.at(currPos[0]).end()){
                    currPos[1]--;
                    direction = 'l';
                }
                else if(direction != 'l' && diagram.at(currPos[0]).find(currPos[1] + 1) != diagram.at(currPos[0]).end()){
                    currPos[1]++;
                    direction = 'r';
                }
            }
            else if(diagram.at(currPos[0]).at(currPos[1]) > 64){
                std::cout << "letter " << "\n";
                res += diagram.at(currPos[0]).at(currPos[1]);
                if(direction == 'u'){
                    currPos[0]--;
                }
                else if(direction == 'd'){
                    currPos[0]++;
                }
                else if(direction == 'l'){
                    currPos[1]--;
                }
                else if(direction == 'r'){
                    currPos[1]++;
                }
            }
        }
        break;       // il n'y a qu'un seul élément de départ
    }
    std::cout << res << "\n";
    return 0;
}