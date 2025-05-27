#include <vector>
#include <iostream>

int main(){
    int circularBufferSize{1};       // la valeur zéro est toujours en première position, si à une étape on arrive au départ on modifie la valeur après zéro car c'est celle qui sera insérée
    int nextInsertion{1};           // à chaque étape on augmente la taille du cache et la prochaine valeur insérée, on met à jour la position actuelle
    int currPos{0};
    int spinSteps{370};
    long afterZero;
    while(nextInsertion <= 50000000){
        if(circularBufferSize - 1 - (currPos + spinSteps) >= 0){    // si la taille du cache est supérieur à la position actuelle plus le déplacement
            currPos = currPos + spinSteps;
            nextInsertion++;
            circularBufferSize++;
            if(currPos == circularBufferSize){
                currPos = 0;
            }
            else currPos++;
        }
        else if(circularBufferSize - 1 - (currPos + spinSteps) < 0){
            int remainingSteps{spinSteps - (circularBufferSize - currPos)};    // le déplacement moins les pas pour revenir à la position zéro
            if(remainingSteps == 0){
                currPos = 0;
                afterZero = nextInsertion;
            }
            else currPos = remainingSteps % circularBufferSize;
            nextInsertion++;
            circularBufferSize++;
            currPos++;
        }
    }
    std::cout << afterZero << "\n";
    return 0;
}