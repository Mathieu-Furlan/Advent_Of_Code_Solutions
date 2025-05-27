#include <fstream>
#include <string>
#include <iostream>

int main(){
    char ch;
    int res{0};
    std::fstream fin("input", std::fstream::in);
    while(fin >> std::noskipws >> ch){
        if(ch == '('){
            res++;
        }
        else if(ch == ')'){
            res--;
        }
    }
    std::cout << res << "\n";
    return res;
}