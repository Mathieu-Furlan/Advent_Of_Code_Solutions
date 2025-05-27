#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    int col{0};
    while(getline(file, s)){
        if(s[col] == '#'){
            res++;
        }
        col = (col + 3) % s.length();
        std::cout << col << "\n";
    }
    std::cout << res << "\n";
    return 0;
}