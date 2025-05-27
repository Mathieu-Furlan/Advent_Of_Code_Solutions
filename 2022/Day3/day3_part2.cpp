#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>
#include <cctype>           // requis pour isupper

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    int countLigns{1};
    std::unordered_set<char> items;
    std::unordered_set<char> itemsCompare;
    char duplicate;
    while(getline(file, s)){
        if(countLigns == 1){
            for(int i = 0; i <= s.length() - 1; i++){
                items.insert(s[i]);
            }
            countLigns++;
        }
        else if(countLigns == 2){
            for(int i = 0; i <= s.length() - 1; i++){
                if(items.find(s[i]) != items.end()){
                    itemsCompare.insert(s[i]);
                }
            }
            countLigns++;
        }
        else if(countLigns == 3){
            for(int i = 0; i <= s.length() - 1; i++){
                if(itemsCompare.find(s[i]) != items.end()){
                    duplicate = s[i];
                    break;
                }
            }
            if(std::isupper(duplicate)){
                res += duplicate - 38;
            }
            else res += duplicate - 96;
            itemsCompare.clear();
            items.clear();
            countLigns = 1;
        }
    }
    std::cout << res << "\n";
    return res;
}