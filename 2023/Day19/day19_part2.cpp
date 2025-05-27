#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, std::string> workFlows;
long long res{0};

void processRatings(int xMin, int xMax, int mMin, int mMax, int aMin, int aMax, int sMin, int sMax, std::string instruction){
    std::cout << "instruction " << instruction << "\n";
    std::cout << "x " << xMin << " " << xMax << " m " << mMin << " " << mMax << " a " << aMin << " " << aMax << " s " << sMin << " " << sMax << "\n";
    std::string instructions{workFlows.at(instruction)};
    int ind{0};
    while(ind <= instructions.length() - 1){
        long unsigned delimeter{instructions.find(',', ind)};
        if(delimeter <= instructions.length() - 1){            // si il reste une comparaison à effectuer
            std::string comparator;
            std::string result;
            for(int j = ind; j <= delimeter; j++){
                if(instructions[j] > 47 && instructions[j] < 58){
                    comparator += instructions[j];
                }
                else if(instructions[j] == ':'){
                    result = instructions.substr(j + 1, delimeter - 1 - j);
                    break;
                }
            }
            if(instructions[ind + 1] == '>'){
                int initialStateMax;
                int initialStateMin;
                if(instructions[ind] == 'x'){                   // on regarde quel intervalle est concerné
                    initialStateMax = xMax;
                    initialStateMin = xMin;
                }
                else if(instructions[ind] == 'm'){
                    initialStateMax = mMax;
                    initialStateMin = mMin;
                }
                else if(instructions[ind] == 'a'){
                    initialStateMax = aMax;
                    initialStateMin = aMin;
                }
                else if(instructions[ind] == 's'){
                    initialStateMax = sMax;
                    initialStateMin = sMin;
                }
                if(initialStateMax > stoi(comparator)){
                    if(initialStateMin <= stoi(comparator)){
                        initialStateMin = stoi(comparator) + 1;    // la valeur minimale de l'intervalle pour l'instruction suivante
                    }
                    if(result.length() > 1){
                        if(instructions[ind] == 'x'){
                            processRatings(initialStateMin, initialStateMax, mMin, mMax, aMin, aMax, sMin, sMax, result);
                            xMax = stoi(comparator);                // pour le reste de la ligne la valeur maximale de x
                        }
                        else if(instructions[ind] == 'm'){
                            processRatings(xMin, xMax, initialStateMin, initialStateMax, aMin, aMax, sMin, sMax, result);
                            mMax = stoi(comparator);                    // pour le reste de la ligne la valeur maximale de m
                        }
                        else if(instructions[ind] == 'a'){
                            processRatings(xMin, xMax, mMin, mMax, initialStateMin, initialStateMax, sMin, sMax, result);
                            aMax = stoi(comparator);                // pour le reste de la ligne la valeur maximale de a
                        }
                        else if(instructions[ind] == 's'){
                            processRatings(xMin, xMax, mMin, mMax, aMin, aMax, initialStateMin, initialStateMax, result);
                            sMax = stoi(comparator);                // pour le reste de la ligne la valeur maximale de s
                        }
                    }
                    else if(result[0] == 'A'){
                        long long tempRes{0};
                        std::cout << "res " << "\n";
                        std::cout << "x " << xMin << " " << xMax << " m " << mMin << " " << mMax << " a " << aMin << " " << aMax << " s " << sMin << " " << sMax << "\n";
                        if(instructions[ind] == 'x'){
                            tempRes += (initialStateMax + 1 - initialStateMin);      // +1 à la valeur maximale car la plus petite valeur de l'intervalle est incluse 
                            tempRes *= (mMax + 1 - mMin);
                            tempRes *= (aMax + 1 - aMin);
                            tempRes *= (sMax + 1 - sMin);
                            xMax = stoi(comparator);                            // pour le reste de la ligne la valeur maximale de x
                        }
                        else if(instructions[ind] == 'm'){
                            tempRes += (initialStateMax + 1 - initialStateMin);
                            tempRes *= (xMax + 1  - xMin);
                            tempRes *= (aMax + 1 - aMin);
                            tempRes *= (sMax +1 - sMin);
                            mMax = stoi(comparator);                        // pour le reste de la ligne la valeur maximale de m
                        }
                        else if(instructions[ind] == 'a'){
                            tempRes += (initialStateMax + 1 - initialStateMin);
                            tempRes *= (xMax + 1 - xMin);
                            tempRes *= (mMax + 1 - mMin);
                            tempRes *= (sMax + 1 - sMin);
                            aMax = stoi(comparator);                        // pour le reste de la ligne la valeur maximale de a
                        }
                        else if(instructions[ind] == 's'){
                            tempRes += (initialStateMax + 1 - initialStateMin);
                            tempRes *= (xMax + 1 - xMin);
                            tempRes *= (mMax + 1 - mMin);
                            tempRes *= (aMax + 1 - aMin);
                            sMax = stoi(comparator);                    // pour le reste de la ligne la valeur maximale de s
                        }
                        res += tempRes;
                        std::cout << "res " << res << "\n";
                    }
                    else if(result[0] == 'R'){                  // même si les valeurs sont rejetées il faut modifier la valeur maximale de l'intervalle
                        if(instructions[ind] == 'x'){
                            xMax = stoi(comparator);                
                        }
                        else if(instructions[ind] == 'm'){
                            mMax = stoi(comparator);
                        }
                        else if(instructions[ind] == 'a'){
                            aMax = stoi(comparator);
                        }
                        else if(instructions[ind] == 's'){
                            sMax = stoi(comparator);
                        }
                    }
                }
            }
            else if(instructions[ind + 1] == '<'){
                int initialStateMax;
                int initialStateMin;
                if(instructions[ind] == 'x'){          // on regarde quel intervalle est concerné
                    initialStateMax = xMax;
                    initialStateMin = xMin;
                }
                else if(instructions[ind] == 'm'){
                    initialStateMax = mMax;
                    initialStateMin = mMin;
                }
                else if(instructions[ind] == 'a'){
                    initialStateMax = aMax;
                    initialStateMin = aMin;
                }
                else if(instructions[ind] == 's'){
                    initialStateMax = sMax;
                    initialStateMin = sMin;
                }
                if(initialStateMin < stoi(comparator)){
                    if(initialStateMax >= stoi(comparator)){               // on prend toutes les valeurs inférieures à la valeur du comparateur
                        initialStateMax = stoi(comparator) - 1;
                    }
                    if(result.length() > 1){
                        if(instructions[ind] == 'x'){
                            processRatings(initialStateMin, initialStateMax, mMin, mMax, aMin, aMax, sMin, sMax, result);
                            xMin = stoi(comparator);                   // pour le reste de la ligne la valeur minimale de x
                        }
                        else if(instructions[ind] == 'm'){
                            processRatings(xMin, xMax, initialStateMin, initialStateMax, aMin, aMax, sMin, sMax, result);
                            mMin = stoi(comparator);                 // pour le reste de la ligne la valeur minimale de m
                        }
                        else if(instructions[ind] == 'a'){
                            processRatings(xMin, xMax, mMin, mMax, initialStateMin, initialStateMax, sMin, sMax, result);
                            aMin = stoi(comparator);                    // pour le reste de la ligne la valeur minimale de a
                        }
                        else if(instructions[ind] == 's'){
                            processRatings(xMin, xMax, mMin, mMax, aMin, aMax, initialStateMin, initialStateMax, result);
                            sMin = stoi(comparator);                // pour le reste de la ligne la valeur minimale de s
                        }
                    }
                    else if(result[0] == 'A'){
                        long long tempRes{0};
                        if(instructions[ind] == 'x'){
                            tempRes += (initialStateMax + 1 - initialStateMin);    // +1 à la valeur maximale car la plus petite valeur de l'intervalle est incluse
                            tempRes *= (mMax + 1 - mMin);
                            tempRes *= (aMax + 1 - aMin);
                            tempRes *= (sMax + 1 - sMin);
                            xMin = stoi(comparator);                            // pour le reste de la ligne la valeur minimale de x
                        }
                        else if(instructions[ind] == 'm'){
                            tempRes += (initialStateMax + 1 - initialStateMin);
                            tempRes *= (xMax + 1 - xMin);
                            tempRes *= (aMax + 1 - aMin);
                            tempRes *= (sMax + 1 - sMin);
                            mMin = stoi(comparator);                        // pour le reste de la ligne la valeur minimale de m
                        }
                        else if(instructions[ind] == 'a'){
                            tempRes += (initialStateMax + 1 - initialStateMin);
                            tempRes *= (xMax + 1 - xMin);
                            tempRes *= (mMax + 1 - mMin);
                            tempRes *= (sMax + 1 - sMin);
                            aMin = stoi(comparator);                    // pour le reste de la ligne la valeur minimale de a
                        }
                        else if(instructions[ind] == 's'){
                            tempRes += (initialStateMax + 1 - initialStateMin);
                            tempRes *= (xMax + 1 - xMin);
                            tempRes *= (mMax + 1 - mMin);
                            tempRes *= (aMax + 1 - aMin);
                            sMin = stoi(comparator);                    // pour le reste de la ligne la valeur minimale de s
                        }
                        res += tempRes;
                        std::cout << "res " << res << "\n";
                    }
                    else if(result[0] == 'R'){                      // même si les valeurs sont rejetées il faut modifier la valeur maximale de l'intervalle
                        if(instructions[ind] == 'x'){
                            xMin = stoi(comparator);
                        }
                        else if(instructions[ind] == 'm'){
                            mMin = stoi(comparator);
                        }
                        else if(instructions[ind] == 'a'){
                            aMin = stoi(comparator);
                        }
                        else if(instructions[ind] == 's'){
                            sMin = stoi(comparator);
                        }
                    }
                }
            }
            ind = delimeter + 1;
        }
        else{                     // si on arrive à la fin de la ligne, toutes les comparaisons sont fausses
            std::string result{instructions.substr(ind)};
            if(result.length() > 1){
                processRatings(xMin, xMax, mMin, mMax, aMin, aMax, sMin, sMax, result);
                return;
            }
            else if(result[0] == 'A'){
                long long tempRes{0};
                tempRes += (aMax + 1 - aMin);       // +1 à la valeur maximale car la plus petite valeur de l'intervalle est incluse
                tempRes *= (xMax + 1 - xMin);
                tempRes *= (mMax + 1 - mMin);
                tempRes *= (sMax + 1 - sMin);
                res += tempRes;
                std::cout << "resEND " << "\n";
                std::cout << "x " << xMin << " " << xMax << " m " << mMin << " " << mMax << " a " << aMin << " " << aMax << " s " << sMin << " " << sMax << "\n";
                std::cout << "resEnd " << res << "\n";
                return;
            }
            else if(result[0] == 'R'){              // si on est à la fin de la ligne ce n'est pas le peine de modifier l'intervalle
                return;
            }
        }
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    while(getline(file, s)){
        if(s[0] > 96 && s[0] < 123){                        // crée une hashmap contenant la première partie du fichier txt
            std::string key;
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] == 123){
                    std::string value{s.substr(i + 1)};
                    value.pop_back();
                    workFlows.insert(std::make_pair(key, value));
                    break;
                }
                else{
                    key += s[i];
                }
            }
        }
    }
    processRatings(1, 4000, 1, 4000, 1, 4000, 1, 4000, "in");
    std::cout << res << "\n";
    return 0;
}