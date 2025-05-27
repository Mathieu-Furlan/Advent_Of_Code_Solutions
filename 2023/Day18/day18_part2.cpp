#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <sstream>

// ne pas utiliser std::abs avec de très grands nombres
int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::array<long, 2>> trench;
    trench.push_back({0, 0});
    long prevCol{0};
    long prevRow{0};
    long perimeter{0};
    while(getline(file, s)){
        unsigned long ind{s.find('#')};
        std::string hexValue{s.substr(ind + 1, 5)};
        long numericalValue;
        std::stringstream ss;
        ss << std::hex << hexValue;
        ss >> numericalValue;
        perimeter += numericalValue;
        if(s[s.length() - 2] == '3'){
            trench.push_back({prevRow + numericalValue, prevCol});
            prevRow += numericalValue;
        }
        else if(s[s.length() - 2] == '1'){
            trench.push_back({prevRow - numericalValue, prevCol});
            prevRow -= numericalValue;
        }
        else if(s[s.length() - 2] == '2'){
            trench.push_back({prevRow, prevCol - numericalValue});
            prevCol -= numericalValue;
        }
        else if(s[s.length() - 2] == '0'){
            trench.push_back({prevRow, prevCol + numericalValue});
            prevCol += numericalValue;
        }
    }
    trench.pop_back();
    for(auto& coordinates : trench){
        std::cout << coordinates[0] << ' ' << coordinates[1] << "\n";
    }
    long firstPart{0};
    long indexA{0};
    while(indexA < trench.size() - 1){
        firstPart += trench[indexA][0] * trench[indexA + 1][1];
        indexA++;
    }
    firstPart += trench[indexA][0] * trench[0][1];
    long secondPart{0};
    long indexB{0};
    while(indexB < trench.size() - 1){
        secondPart += trench[indexB][1] * trench[indexB + 1][0];
        indexB++;
    }
    secondPart += trench[indexB][1] * trench[0][0];
    std::cout << firstPart << "\n";
    std::cout << secondPart << "\n";
    long shoeLace{(firstPart - secondPart) / 2};     // résultat de la formule shoelace qui est symbolisé par A dans le théorème de Pick
    std::cout << shoeLace << "\n";
    long res{shoeLace + perimeter / 2 + 1};        // on applique le théorème de Pick avec b pour le périmètre:
    std::cout << res << "\n";                     // - théorème de Pick: A = i + b / 2 - 1 avec i les polongs longernes, b les polongs sur le périmètre, a l'aire totale
    return 0;                                     // - on en déduit i = A - b / 2 + 1 puis i + b = A + b / 2 + 1
}