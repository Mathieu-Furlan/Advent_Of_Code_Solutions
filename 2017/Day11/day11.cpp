#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    double verticalDistance{0};
    double horizontalDistance{0};
    while(getline(file, s)){
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == 's'){
                if(s[i + 1] == ','){
                    verticalDistance--;
                }
                else if(s[i + 1] == 'e'){
                    verticalDistance -= 0.5;
                    horizontalDistance += 0.5;
                }
                else if(s[i + 1] == 'w'){
                    verticalDistance -= 0.5;
                    horizontalDistance -= 0.5;
                }
                std::cout << verticalDistance << "\n";
                std::cout << horizontalDistance << "\n";
            }
            else if(s[i] == 'n'){
                if(s[i + 1] == ','){
                    verticalDistance++;
                }
                else if(s[i + 1] == 'e'){
                    verticalDistance += 0.5;
                    horizontalDistance += 0.5;
                }
                else if(s[i + 1] == 'w'){
                    verticalDistance += 0.5;
                    horizontalDistance -= 0.5;
                }
                std::cout << verticalDistance << "\n";
                std::cout << horizontalDistance << "\n";
            }
        }
    }
    std::cout << verticalDistance << "\n";
    std::cout << horizontalDistance << "\n";
    // en se déplaçant en diagonale on parcourt 0,5 unité de distance horizontalement et verticalement en un pas
    // on enlève ou on ajoute 0,5 à verticalDistance et horizontalDistance jusqu'à ce que l'un soit à zéro; à chaque fois le résultat augmente de 1
    // si verticalDistance et supérieur à horizontalDistance on ajoute la différence au résultat
    // sinon si horizontalDistance est plus grand on multiplie par deux la différence car on ne peut pas se déplacer horizontalement en un pas, il faut deux pas en diagonale
    return 0;
}