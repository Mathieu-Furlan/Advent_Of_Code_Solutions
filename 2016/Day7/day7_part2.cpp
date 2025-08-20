#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        std::unordered_set<std::string> inside;
        std::unordered_set<std::string> outside;
        bool brackets{false};
        for(int i = 0; i < s.length() - 2; i++){
            if(s[i] == '['){
                brackets = true;
            }
            else if(s[i] == ']'){
                brackets = false;
            }
            else{
                if(s[i] == s[i + 2] && s[i + 1] != s[i] && s[i + 1] > 96 && s[i + 1] < 123){
                    std::string reverse{s.substr(i + 1, 2)};
                    if(brackets){
                        if(outside.find(reverse) != outside.end()){
                            res++;
                            break;
                        }
                        else{
                            inside.insert(s.substr(i, 2));
                        }
                    }
                    else{
                        if(inside.find(reverse) != inside.end()){
                            res++;
                            break;
                        }
                        else{
                            outside.insert(s.substr(i, 2));
                        }
                    }
                }
            }
        }
    }
    std::cout << res << "\n";
    return 0;
}