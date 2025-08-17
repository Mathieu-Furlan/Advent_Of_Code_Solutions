#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        bool brackets{false};
        bool tls{false};
        for(int i = 0; i < s.length() - 3; i++){
            if(s[i] == '['){
                brackets = true;
            }
            else if(s[i] == ']'){
                brackets = false;
            }
            if(s[i] != s[i + 1] && s[i] == s[i + 3] && s[i + 1] == s[i + 2]){
                if(brackets){
                    tls = false;
                    break;
                }
                else tls = true;
            }
        }
        if(tls){
            res++;
        }
    }
    std::cout << res << "\n";
    return 0;
}