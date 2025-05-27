#include <fstream>
#include <string>
#include <iostream>
#include <array>

std::array<int, 2> processObject(std::string jsonString){
    std::string addNumber;
    bool toAdd{false};
    bool negative{false};
    bool red{false};
    int tempRes{0};
    for(int i = 0; i <= jsonString.length() - 1; i++){
        if(jsonString[i] > 47 && jsonString[i] < 58){
            if(addNumber.length() == 0 && jsonString[i - 1] == '-'){
                negative = true;
            }
            addNumber += jsonString[i];
            toAdd = true;
        }
        else if(jsonString[i] == '{'){
            std::array<int, 2> results{processObject(jsonString.substr(i + 1))};
            i += 1 + results[0];  // on déplace i pour ne pas compter deux fois le contenu entre accolades, + 1 car la boucle for de la fonction récursive commence à 0
            tempRes += results[1];  // on incremente tempRes des résultats trouvés dans les éléments imbriqués
        }
        else if(jsonString[i] == '}'){
            if(toAdd){
                if(negative){
                    tempRes -= std::stoi(addNumber);
                }
                else tempRes += std::stoi(addNumber);
            }
            if(red){
                tempRes = 0;    // si red on annule le résultat en cours et celui de tous les éléments imbriqués
            }
            return {i, tempRes};   // on renvoie l'indice de fin de l'élément imbriqué et le résulat de l'élément et de tous ses enfants
        }
        else if(jsonString[i] == 'r'){
            if(jsonString[i - 2] == ':' && jsonString[i + 1] == 'e' && jsonString[i + 2] == 'd'){
                red = true;
            }
        }
        else if(toAdd){
            if(negative){
                tempRes -= std::stoi(addNumber);
                negative = false;
            }
            else tempRes += std::stoi(addNumber);
            addNumber.clear();
            toAdd = false;
        }
    }
    return {0, 0};  // on arrive jamais là car les accolades ouvertes sont obligatoirement
}

int main(){
    int res{0};
    std::ifstream file("input");
    std::string addNumber;
    std::string s;
    bool toAdd{false};
    bool negative{false};
    while(getline(file, s)){
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 47 && s[i] < 58){
                if(addNumber.length() == 0 && s[i - 1] == '-'){
                    negative = true;
                }
                addNumber += s[i];
                toAdd = true;
            }
            else if(s[i] == '{'){
                std::array<int, 2> mainResults{processObject(s.substr(i + 1))};
                i += 1 + mainResults[0];
                res += mainResults[1];
            }
            else if(toAdd){
                if(negative){
                    res -= std::stoi(addNumber);
                    negative = false;
                }
                else res += std::stoi(addNumber);
                addNumber.clear();
                toAdd = false;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}