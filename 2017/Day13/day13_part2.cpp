#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<int, int> layers;
    while(getline(file, s)){
        std::string picoSecond;
        std::string scanner;
        bool layer{false};
        for(int i = 0; i <= s.length() - 1; i++){
            if(i == 0){
                while(s[i] > 47 && s[i] < 58){
                    picoSecond += s[i];
                    i++;
                }
                layer = true;
            }
            else if(s[i] > 47 && s[i] < 58){
                scanner += s[i];
            }
        }
        int scanVal{std::stoi(scanner)};
        int elapsedTime{std::stoi(picoSecond)};
        layers.insert(std::make_pair(elapsedTime, scanVal));
    }
    bool pass{false};
    int delay{1};
    while(!pass){
        bool caught{false};
        for(auto& [key, value] : layers){
            if((key + delay) % ((value - 1) * 2) == 0){   // si le délai plus le nombre de picosecondes est égal à la taille du scanner moins un multipliée par deux alors le paquet est intercepté
                caught = true;
                break;
            }
        }
        if(!caught){
            pass = true;
        }
        else delay++;
    }
    std::cout << delay << "\n";
    return delay;
}