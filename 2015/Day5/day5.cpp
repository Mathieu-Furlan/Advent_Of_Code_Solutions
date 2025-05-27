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
        int vowelCount{0};
        bool twice{false};
        bool combination{false};
        std::unordered_set<char> vowelsFound;
        for(int i = 0; i <= s.length() - 1; i++){
            if(vowels.find(s[i]) != vowels.end() && vowelsFound.find(s[i]) == vowelsFound.end()){
                vowelCount++;
            }
            if(!twice && i > 0 && s[i] == s[i - 1]){
                twice = true;
            }
            if(i > 0 && (s[i] == 'b' || s[i] == 'd' || s[i] == 'q' || s[i] == 'y') && s[i - 1] == s[i] - 1){
                combination = true;
            }
        }
        if(vowelCount >= 3 && twice && !combination){
            res++;
        }
    }
    std::cout << res << "\n";
    return res;
}