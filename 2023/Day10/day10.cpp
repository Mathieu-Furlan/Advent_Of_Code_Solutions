#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::vector<char>> matrix;
    int startLign{0};
    int startColumn{0};
    int lign{0};
    int stepsLoop{0};
    while(getline(file, s)){
        std::vector<char> temp;
        for(int i = 0; i <= s.length() - 1; i++){
            temp.push_back(s[i]);
            if(s[i] == 'S'){
                startColumn = i;
                startLign = lign;
            }
        }
        matrix.push_back(temp);
        lign++;
    }
    int precedent[2];                                 //precedent pour ne pas revenir en arrière
    precedent[0] = startLign;
    precedent[1] = startColumn;
    std::stack<std::array<int, 2>> stackPath;         //stack qui contient les coordonées actuelles
    stackPath.push({startLign, startColumn});
    while(!stackPath.empty()){
        int currLign{stackPath.top()[0]};
        int currCol{stackPath.top()[1]};
        std::cout << "lign " << currLign << "\n";
        std::cout << "column " << currCol << "\n";
        if(matrix[currLign][currCol] == 'S' && stepsLoop > 0){
            break;
        }
        stackPath.pop();                                //on vérifie le symbole de la prochaine case et le symbole actuel
        if(currLign + 1 != precedent[0] && (matrix[currLign + 1][currCol] == '|' || matrix[currLign + 1][currCol] == 'L' || matrix[currLign + 1][currCol] == 'J') && (matrix[currLign][currCol] == '7' || matrix[currLign][currCol] == 'F' || matrix[currLign][currCol] == '|' || matrix[currLign][currCol] == 'S')){
            stackPath.push({currLign + 1, currCol});
        }
        else if(currLign - 1 != precedent[0] && (matrix[currLign - 1][currCol] == '|' || matrix[currLign - 1][currCol] == '7' || matrix[currLign - 1][currCol] == 'F') && (matrix[currLign][currCol] == 'J' || matrix[currLign][currCol] == 'L' || matrix[currLign][currCol] == '|' || matrix[currLign][currCol] == 'S')){
            stackPath.push({currLign - 1, currCol});
        }
        else if(currCol + 1 != precedent[1] && (matrix[currLign][currCol + 1] == '-' || matrix[currLign][currCol + 1] == '7' || matrix[currLign][currCol + 1] == 'J') && (matrix[currLign][currCol] == 'L' || matrix[currLign][currCol] == 'F' || matrix[currLign][currCol] == '-' || matrix[currLign][currCol] == 'S')){
            stackPath.push({currLign, currCol + 1});
        }
        else if(currCol - 1 != precedent[1] && (matrix[currLign][currCol - 1] == '-' || matrix[currLign][currCol - 1] == 'F' || matrix[currLign][currCol - 1] == 'L') && (matrix[currLign][currCol] == '7' || matrix[currLign][currCol] == 'J' || matrix[currLign][currCol] == '-' || matrix[currLign][currCol] == 'S')){
            stackPath.push({currLign, currCol - 1});
        }
        stepsLoop++;
        precedent[0] = currLign;          // les valeurs de précédent correspondent aux coordonnées deux étapes précédemment
        precedent[1] = currCol;
    }
    std::cout << stepsLoop << "\n";       
    std::cout << stepsLoop / 2 << "\n";     // le point le plus éloigné est celui qui correspond au nombre d'éléments de la boucle divisé par deux
    return stepsLoop / 2;
}