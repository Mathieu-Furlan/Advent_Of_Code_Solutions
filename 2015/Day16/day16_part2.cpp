#include <fstream>
#include <string>
#include <iostream>

struct aunts{
    aunts(): children(3), cats(7), samoyeds(2), pomeranians(3), 
    akitas(0), vizslas(0), goldfish(5), trees(3), cars(2), perfumes(1) {} // constructeur par défaut pas utile dans ce cas
    int children;
    int cats;
    int samoyeds;
    int pomeranians;
    int akitas;
    int vizslas;
    int goldfish;
    int trees;
    int cars;
    int perfumes;
}giftAunt;

int main(){
    std::ifstream file("input");
    std::string s;
    int numberAunt{0};
    while(getline(file, s)){
        numberAunt++;
        struct aunts currAunt = giftAunt;      // par défaut les deux structs sont identiques
        bool nextAunt{false};
        bool attributes{false};
        for(int i = 5; i <= s.length() - 1; i++){
            if(s[i] == ':'){
                attributes = true;
            }
            if(attributes){
                if(s[i] == 'g'){
                    if(i + 11 != s.length() && s[i + 11] != ','){
                        nextAunt = true;
                        break;
                    }
                    int attributeVal = s[i + 10] - '0';
                    currAunt.goldfish = attributeVal;
                    if(currAunt.goldfish >= giftAunt.goldfish){
                        nextAunt = true;
                        break;
                    }
                    i += 11;
                }
                else if(s[i] == 's'){
                    if(i + 11 != s.length() && s[i + 11] != ','){
                        nextAunt = true;
                        break;
                    }
                    int attributeVal = s[i + 10] - '0';
                    currAunt.samoyeds = attributeVal;
                    i += 11;
                }
                else if(s[i] == 'c' && s[i + 1] == 'h'){
                    if(i + 11 != s.length() && s[i + 11] != ','){
                        nextAunt = true;
                        break;
                    }
                    int attributeVal = s[i + 10] - '0';
                    currAunt.children = attributeVal;
                    i += 11;
                }
                else if(s[i] == 'c' && s[i + 2] == 't'){
                    std::string tempString;
                    tempString += s[i + 6];
                    if(i + 7 != s.length() && s[i + 7] != ','){
                        tempString += s[i + 7];
                    }
                    currAunt.cats = std::stoi(tempString);
                    if(currAunt.cats <= giftAunt.cats){
                        nextAunt = true;
                        break;
                    }
                    i += 7;
                }
                else if(s[i] == 'c' && s[i + 2] == 'r'){
                    if(i + 7 != s.length() && s[i + 7] != ','){
                        nextAunt = true;
                        break;
                    }
                    int attributeVal = s[i + 6] - '0';
                    currAunt.cars = attributeVal;
                    i += 7;
                }
                else if(s[i] == 'p' && s[i + 1] == 'o'){
                    if(i + 14 != s.length() && s[i + 14] != ','){
                        nextAunt = true;
                        break;
                    }
                    int attributeVal = s[i + 13] - '0';
                    currAunt.pomeranians = attributeVal;
                    if(currAunt.pomeranians >= giftAunt.pomeranians){
                        nextAunt = true;
                        break;
                    }
                    i += 14;
                }
                else if(s[i] == 'a'){
                    if(i + 9 != s.length() && s[i + 9] != ','){
                        nextAunt = true;
                        break;
                    }
                    int attributeVal = s[i + 8] - '0';
                    currAunt.akitas = attributeVal;
                    i += 9;
                }
                else if(s[i] == 'v'){
                    if(i + 10 != s.length() && s[i + 10] != ','){
                        nextAunt = true;
                        break;
                    }
                    int attributeVal = s[i + 9] - '0';
                    currAunt.vizslas = attributeVal;
                    i += 10;
                }
                else if(s[i] == 't'){
                    std::string tempString;
                    tempString += s[i + 7];
                    if(i + 8 != s.length() && s[i + 8] != ','){
                        tempString += s[i + 8];
                    }
                    currAunt.trees = std::stoi(tempString);
                    if(currAunt.trees <= giftAunt.trees){
                        nextAunt = true;
                        break;
                    }
                    i += 8;
                }
                else if(s[i] == 'p' && s[i + 1] == 'e'){
                    if(i + 11 != s.length() && s[i + 11] != ','){
                        nextAunt = true;
                        break;
                    }
                    int attributeVal = s[i + 10] - '0';
                    currAunt.perfumes = attributeVal;
                    i += 11;
                }
            }
        }
        if(!nextAunt){                               // on vérifie que les attributs des deux structs sont identiques
            if(currAunt.children == giftAunt.children && currAunt.samoyeds == giftAunt.samoyeds && 
            currAunt.akitas == giftAunt.akitas && currAunt.vizslas == giftAunt.vizslas && 
            currAunt.cars == giftAunt.cars && currAunt.perfumes == giftAunt.perfumes){
                std::cout << numberAunt << "\n";
                return numberAunt;
            }
        }
    }
    return 0;     // on n'arrive jamais là
}