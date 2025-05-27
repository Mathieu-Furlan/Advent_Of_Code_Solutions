#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>
#include <cctype>            // requis pour isupper

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        char duplicate;
        std::unordered_set<char> items;
        for(int i = 0; i <= s.length() / 2 - 1; i++){
            items.insert(s[i]);
        }
        for(int j = s.length() / 2; j <= s.length() - 1; j++){
            if(items.find(s[j]) != items.end()){
                duplicate = s[j];
                break;
            }
        }
        if(std::isupper(duplicate)){
            res += duplicate - 38;
        }
        else res += duplicate - 96;
    }
    std::cout << res << "\n";
    return res;
}