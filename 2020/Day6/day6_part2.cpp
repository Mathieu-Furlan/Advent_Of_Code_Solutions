#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::unordered_set<char> questions;
    for(int i = 97; i <= 122; i++){
        questions.insert(i);
    }
    while(getline(file, s) || file.peek() == EOF){
        if(s.length() == 0){
            for(auto& answers : questions){
                res++;
            }
            for(int i = 97; i <= 122; i++){
                questions.insert(i);
            }
        }
        else{
            std::vector<char> toBeDeleted;
            for(auto& letter : questions){
                if(s.find(letter) == std::string::npos){            // npos signifie jusqu'à la fin de la chaîne de caractères
                    toBeDeleted.push_back(letter);
                }
            }
            for(auto& deleted : toBeDeleted){
                questions.erase(deleted);
            }
        }
        if(file.eof()){
            break;
        }
    }
    std::cout << res << "\n";
    return 0;
}