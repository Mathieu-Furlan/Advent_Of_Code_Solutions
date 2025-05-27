// brute force est trop lent, on cherche le diviseur commun le plus petit (ppcm)

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>


int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::vector<char> directions;
    getline(file, s);
    for(int i = 0; i <= s.length() - 1; i++){
        directions.push_back(s[i]);
    }
    getline(file, s);
    std::unordered_map<std::string, std::string> elements;
    std::vector<std::string> starting;
    std::vector<bool> atDestination;
    std::vector<int> choices;
    while(getline(file, s)){
        std::string key;
        std::string val;
        key.push_back(s[0]);
        key.push_back(s[1]);
        key.push_back(s[2]);
        if(s[2] == 'A'){
            starting.push_back(key);
            atDestination.push_back(false);
            choices.push_back(0);         // pour chaque élément on calcule le nombre d'étapes avant d'arriver à une node qui se termine par Z
        }
        val.push_back(s[7]);
        val.push_back(s[8]);
        val.push_back(s[9]);
        val.push_back(s[12]);
        val.push_back(s[13]);
        val.push_back(s[14]);
        elements.insert(std::make_pair(key, val));   // utiliser make_pair pour insérer un duo cle/valeur;
    }
    int destination{0};
    for(int j = 0; j <= directions.size() - 1; j = (j + 1) % directions.size()){
        if(directions[j] == 'L'){
            for(int k = 0; k <= starting.size() - 1; k++){
                if(!atDestination[k]){
                    starting[k] = elements.at(starting[k]).substr(0, 3);
                    choices[k]++;
                    if(starting[k][2] == 'Z'){                 //un seul apostrophe pour char, deux pour string;
                        destination++;
                        atDestination[k] = true;
                    }
                }
            }
        }
        else{
            for(int k = 0; k <= starting.size() - 1; k++){
                if(!atDestination[k]){
                    starting[k] = elements.at(starting[k]).substr(3);
                    choices[k]++;
                    if(starting[k][2] == 'Z'){                 //un seul apostrophe pour char, deux pour string;
                        destination++;
                        atDestination[k] = true;
                    }
                }
            }
        }
        res++;
        if(destination == starting.size()){
            break;
        }
    }
    long long leastCommonMultiple{std::lcm(choices[0], choices[1])};    // long long car la valeur maximale de int n'est pas suffisante
    std::cout << "lcm" << leastCommonMultiple << "\n";
    for(int m = 2; m <= choices.size() - 1; m++){
        leastCommonMultiple = std::lcm(choices[m], leastCommonMultiple);  // ltd::lcm pour least common multiple
        std::cout << "lcm " << leastCommonMultiple << "\n";
        std::cout << "choice " << choices[m] << "\n";
    }
    std::cout << leastCommonMultiple << "\n";
    return leastCommonMultiple;
}