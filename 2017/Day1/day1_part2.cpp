#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    getline(file, s);
    int halfSize(s.length() / 2);
    for(int i = 0; i <= s.length() - 1; i++){
        long unsigned compIndex{(i + halfSize) % s.length()};
        if(s[i] == s[compIndex]){
            res += s[i] - '0';
        }
    }
    std::cout << res << "\n";
    return res;
}