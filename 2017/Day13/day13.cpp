#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
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
        if(elapsedTime % (scanVal - 1) == 0 && elapsedTime / (scanVal - 1) % 2 == 0){ // le nombre de fois où le scanner parcours sa zone doit être pair pour être en position initiale
            std::cout << picoSecond << "\n";
            res += elapsedTime * scanVal;
        }
    }
    std::cout << res << "\n";
    return res;
}