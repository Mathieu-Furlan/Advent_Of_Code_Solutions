#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        std::unordered_set<std::string> passwords;
        std::string wordConstructor;
        bool duplicate{false};
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 96 && s[i] < 123){
                wordConstructor += s[i];
            }
            else{
                if(passwords.find(wordConstructor) == passwords.end()){
                    passwords.insert(wordConstructor);
                }
                else{
                    duplicate = true;
                    break;
                }        
                wordConstructor.clear();
            }
        }
        if(passwords.find(wordConstructor) == passwords.end()){
            passwords.insert(wordConstructor);
        }
        else duplicate = true;
        if(!duplicate){
            res++;
        }
    }
    std::cout << res << "\n";
    return res;
}