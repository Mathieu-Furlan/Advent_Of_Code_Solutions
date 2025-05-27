#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>

// on applique la formule shoelace
int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<int, 2>> trench;
    trench.push_back({1000, 1000});
    int prevCol{1000};
    int prevRow{1000};
    int perimeter{0};
    while(getline(file, s)){
        std::string value;
        int ind{2};
        while(s[ind] > 47 && s[ind] < 58){
            value += s[ind];
            ind++;
        }
        int numericalValue{std::stoi(value)};
        perimeter += numericalValue;
        if(s[0] == 'U'){
            trench.push_back({prevRow + numericalValue, prevCol});
            prevRow += numericalValue;
        }
        else if(s[0] == 'D'){
            trench.push_back({prevRow - numericalValue, prevCol});
            prevRow -= numericalValue;
        }
        else if(s[0] == 'L'){
            trench.push_back({prevRow, prevCol - numericalValue});
            prevCol -= numericalValue;
        }
        else if(s[0] == 'R'){
            trench.push_back({prevRow, prevCol + numericalValue});
            prevCol += numericalValue;
        }
    }
    trench.pop_back();
    for(auto& coordinates : trench){
        std::cout << coordinates[0] << ' ' << coordinates[1] << "\n";
    }
    int firstPart{0};
    int indexA{0};
    while(indexA < trench.size() - 1){
        firstPart += trench[indexA][0] * trench[indexA + 1][1];
        indexA++;
    }
    firstPart += trench[indexA][0] * trench[0][1];
    int secondPart{0};
    int indexB{0};
    while(indexB < trench.size() - 1){
        secondPart += trench[indexB][1] * trench[indexB + 1][0];
        indexB++;
    }
    secondPart += trench[indexB][1] * trench[0][0];
    std::cout << firstPart << "\n";
    std::cout << secondPart << "\n";
    int shoeLace{(firstPart - secondPart) / 2};     // résultat de la formule shoelace qui est symbolisé par A dans le théorème de Pick
    std::cout << shoeLace << "\n";
    int res{shoeLace + perimeter / 2 + 1};        // on applique le théorème de Pick avec b pour le périmètre:
    std::cout << res << "\n";                     // - théorème de Pick: A = i + b / 2 - 1 avec i les points internes, b les points sur le périmètre, a l'aire totale
    return 0;                                     // - on en déduit i = A - b / 2 + 1 puis i + b = A + b / 2 + 1
}