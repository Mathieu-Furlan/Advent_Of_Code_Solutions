#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

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
    while(getline(file, s)){
        std::string key;
        std::string val;
        key.push_back(s[0]);
        key.push_back(s[1]);
        key.push_back(s[2]);
        val.push_back(s[7]);
        val.push_back(s[8]);
        val.push_back(s[9]);
        val.push_back(s[12]);
        val.push_back(s[13]);
        val.push_back(s[14]);
        elements.insert(std::make_pair(key, val));   // utiliser make_pair pour insérer un duo cle/valeur;
    }
    std::string currentElem = "AAA";
    for(int j = 0; j <= directions.size() - 1; j = (j + 1) % directions.size()){
        std::cout << currentElem << "\n";
        if(directions[j] == 'L'){                     //un seul apostrophe pour char, deux pour string;
            currentElem = elements.at(currentElem).substr(0, 3);
        }
        else currentElem = elements.at(currentElem).substr(3);
        res++;
        if(currentElem == "ZZZ"){
            break;
        }
    }
    std::cout << res << "\n";
    return res;
}