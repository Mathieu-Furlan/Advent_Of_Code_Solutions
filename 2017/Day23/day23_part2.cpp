#include <iostream>
                                // on simplifie le code donné
int main(){                     // le résultat est égal à 1000 moins le nombre de nombres premiers entre 108400 et 125400
    int h{0};
    for(int i = 108400; i <= 125400; i = i + 17){
        for(int j = 2; j < i; j++){
            if(i % j == 0){
                h++;
                break;
            }
        }
    }
    std::cout << h << "\n";
    return h;
}