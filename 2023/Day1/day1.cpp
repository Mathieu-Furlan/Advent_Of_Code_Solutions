#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream infile("input");
    std::string s;
    int res = 0;
    while(infile >> s){
        int gauche = 0;
        while(s[gauche] > 57){
            gauche++;
        }
        int droite = s.length() - 1;
        while(s[droite] > 57){
            droite--;
        }
        std::string nbre = std::string() + s[gauche] + s[droite];
        int temp{std::stoi(nbre)};
        res = res + temp;
    }
    std::cout << res << "\n";
    return res;
}
