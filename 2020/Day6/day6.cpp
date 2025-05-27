#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::unordered_set<char> questions;
    while(getline(file, s) || file.peek() == EOF){
        if(s.length() == 0){
            for(auto& answers : questions){
                res++;
            }
            questions.clear();
        }
        else{
            for(auto& letter : s){
                questions.insert(letter);
            }
        }
        if(file.eof()){
            break;
        }
    }
    std::cout << res << "\n";
    return 0;
}