#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    getline(file, s);
    for(int i = 0; i <= s.length() - 2; i++){
        if(s[i] == s[i + 1]){
            res += s[i] - '0';
        }
    }
    if(s[s.length() - 1] == s[0]){
        res += s[s.length() - 1] - '0';
    }
    std::cout << res << "\n";
    return res;
}