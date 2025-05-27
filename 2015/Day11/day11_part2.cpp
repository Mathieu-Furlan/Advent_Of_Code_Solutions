#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(){
    std::string puzzleInput{"hepxxyzz"};
    int letterIndex{7};
    bool found{false};
    while(!found){
        bool nextPassword{true};
        puzzleInput[letterIndex]++;
        for(int i = 0; i <= puzzleInput.length() - 1; i++){
            if(puzzleInput[i] == 'i' || puzzleInput[i] == 'o' || puzzleInput[i] == 'l'){
                nextPassword = false;
            }
        }
        if(nextPassword){
            bool straightIncrease{false};
            for(int i = 2; i <= puzzleInput.length() - 1; i++){
                if(puzzleInput[i] == puzzleInput[i - 1] + 1 && puzzleInput[i - 1] == puzzleInput[i - 2] + 1){
                    straightIncrease = true;
                }
            }
            if(!straightIncrease){
                nextPassword = false;
            }
        }
        if(nextPassword){
            int pairs{0};
            std::vector<int> indexPairs;
            for(int i = 1; i <= puzzleInput.length() - 1; i++){
                if(puzzleInput[i] == puzzleInput[i - 1] && std::find(indexPairs.begin(), indexPairs.end(), i) == indexPairs.end() && std::find(indexPairs.begin(), indexPairs.end(), i - 1) == indexPairs.end()){
                    indexPairs.push_back(i);
                    indexPairs.push_back(i - 1);
                    pairs++;
                }
            }
            if(pairs < 2){
                nextPassword = false;
            }
        }
        if(nextPassword){
            found = true;
            std::cout << puzzleInput << "\n";
        }
        if(puzzleInput[letterIndex] == 123){            // si on a considéré toutes les possiblités pour la lettre finale
            puzzleInput[letterIndex] = 'a';
            letterIndex--;
            while(puzzleInput[letterIndex] == 'z'){         // on parcourt les lettres vers la gauche jusqu'à en trouver une qui ne soit pas z
                puzzleInput[letterIndex] = 'a';
                letterIndex--;
            }
            puzzleInput[letterIndex]++;                 // on passe à la lettre suivante pour la première lettre différente de z trouvée
            letterIndex = 7;
        }
    }
    return 0;
}