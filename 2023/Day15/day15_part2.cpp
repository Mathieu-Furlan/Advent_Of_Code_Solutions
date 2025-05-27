#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>

int main(){
    char ch;
    int res{0};
    int boxValue{0};
    std::string label;
    std::array<std::vector<std::string>, 256> hashMap;
    std::fstream fin("input", std::fstream::in);
    while(fin >> std::noskipws >> ch){
        if(ch >= 97 && ch <= 122){
            boxValue += ch;
            label.push_back(ch);
            boxValue *= 17;
            boxValue = boxValue % 256;
        }
        else if(ch == 61){                                                  // si =
            bool exist{false};
            if(hashMap[boxValue].size() > 0){                               // vérifie si label est déjà présent à l'index boxValue
                for(int i = 0; i <= hashMap[boxValue].size() - 1; i++){
                    std::cout << "i " << i << "\n";
                    if(hashMap[boxValue][i].substr(0, hashMap[boxValue][i].length() - 1) == label){
                        label.push_back(fin.peek());
                        hashMap[boxValue][i] = label;
                        exist = true;
                        break;
                    }
                }
            }
            if(!exist){
                label.push_back(fin.peek());
                hashMap[boxValue].push_back(label);
            }
            label.clear();
            boxValue = 0;
        }
        else if(ch == 45){                                              // si -
            if(hashMap[boxValue].size() > 0){                   // vérifie que la taille n'est pas nulle pour éviter une segmentation fault
                for(int i = 0; i <= hashMap[boxValue].size() - 1; i++){
                    if(hashMap[boxValue][i].substr(0, hashMap[boxValue][i].length() - 1) == label){
                        hashMap[boxValue].erase(hashMap[boxValue].begin() + i);
                        break;
                    }
                }
            }
            label.clear();
            boxValue = 0;
        }
    }
    for(int j = 0; j <= hashMap.size() - 1; j++){
        if(hashMap[j].size() > 0){                                    // vérifie la taille pour éviter une segmentation fault
            for(int k = 0; k <= hashMap[j].size() - 1; k++){
                res += (1 + j) * (1 + k) * (hashMap[j][k][hashMap[j][k].length() - 1] - 48);      // 48 est 0 dans la table ascii
                std::cout << "focalLength " << hashMap[j][k][hashMap[j][k].length() - 1] << "\n";
                std::cout << "j " << j << "\n";
                std::cout << "k " << k << "\n";
                std::cout << res << "\n";
            }
        }
    } 
    std::cout << res << "\n";
    return res;
}