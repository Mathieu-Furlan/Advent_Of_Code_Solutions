#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        std::vector<std::unordered_map<char, int>> wordList;
        std::unordered_map<char, int> passwords;
        bool validPhrase{true};
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 96 && s[i] < 123){
                if(passwords.find(s[i]) == passwords.end()){
                    passwords.insert(std::make_pair(s[i], 1));
                }
                else passwords.at(s[i])++;
            }
            else{
                for(auto& word : wordList){
                    bool duplicate{true};
                    if(passwords.size() != word.size()){
                        duplicate = false;
                    }
                    for(auto& [key, value] : passwords){
                        if(word.find(key) == word.end() || value != word.at(key)){
                            duplicate = false;
                        }
                    }
                    if(duplicate){
                        validPhrase = false;
                        break;
                    }
                }
                if(validPhrase){
                    wordList.push_back(passwords);
                    passwords.clear();
                }
                else break;
            }
        }
        for(auto& word : wordList){       // vérification pour le dernier mot de la phrase
            bool duplicate{true};
            if(passwords.size() != word.size()){
                duplicate = false;
            }
            for(auto& [key, value] : passwords){
                if(word.find(key) == word.end() || value != word.at(key)){
                    duplicate = false;
                }
            }
            if(duplicate){
                validPhrase = false;
                break;
            }
        }
        if(validPhrase){
            res++;
        }
    }
    std::cout << res << "\n";
    return res;
}