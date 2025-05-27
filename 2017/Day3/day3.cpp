#include <iostream>
#include <cmath>

// la valeur dans le coin en bas à droite est égale au carré de la racine carrée du nombre précédent en bas à droite plus deux
// chaque cercle contient huit valeurs de plus que le précédent (1,8,16,24,32,40....)
// 347991 se situe entre le quart et la moitié des 2360 éléments du 295ème cercle, on en déduit qu'il se trouve sur la partie verticale supérieure de la spirale;
// la valeur du coin supérieur gauche est 346921 + 2360 / 2 = 348101; il y a 2360 / 4 = 590 éléments sur chaque axe;
// l'index de la valeur directement au dessus de 1 est donc 590 / 2 = 295;
// l'écart entre 348101 et la valeur cible 347991 est de 110;
// le nombre de pas est 295 - 110 + 295 = 480, c'est 295 vers le haut car la valeur se trouve sur le 295ème cercle plus un décalage à gauche de 185;

int main(){
    int bottomRight{1};
    int circles{0};
    int circleElems{0};
    while(std::pow(bottomRight, 2) < 347991){
        bottomRight += 2;
        circles++;
        circleElems += 8;
    }
    double bottomRightValue{std::pow(bottomRight, 2)};
    double dist{bottomRightValue - 347991};
    double prevBottomRightValue{std::pow(bottomRight - 2, 2)};
    std::cout << prevBottomRightValue << "\n";
    std::cout << circleElems << "\n";
    std::cout << circles << "\n";
    return 0;
}