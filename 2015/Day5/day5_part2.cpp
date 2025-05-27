#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>

int main(){
    std::ifstream infile("input");
    std::string s;
    std::unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};
    int res{0};
    while(infile >> s){
        bool twice{false};
        bool repeat{false};
        std::unordered_set<char> vowelsFound;
        for(int i = 0; i <= s.length() - 1; i++){
            if(!repeat && i > 0 && s[i] == s[i - 2]){
                repeat = true;
            }
        }
        for(int i = 1; i <= s.length() - 1; i++){
            char a1{s[i - 1]};
            char a2{s[i]};
            for(int j = i + 2; j <= s.length() - 1; j++){
                char b1{s[j - 1]};
                char b2{s[j]};
                if(a1 == b1 && a2 == b2){
                    twice = true;
                    break;
                }
            }
            if(twice){
                break;
            }
        }
        if(twice && repeat){
            res++;
        }
    }
    std::cout << res << "\n";
    return res;
}