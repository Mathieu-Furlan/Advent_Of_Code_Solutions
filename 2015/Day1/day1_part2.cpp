#include <fstream>
#include <string>
#include <iostream>

int main(){
    char ch;
    int res{0};
    int index{1};
    std::fstream fin("input", std::fstream::in);
    while(fin >> std::noskipws >> ch){
        if(ch == '('){
            res++;
        }
        else if(ch == ')'){
            res--;
        }
        if(res == -1){
            std::cout << index << "\n";
            return index;
        }
        index++;
    }
    std::cout << res << "\n";
    return res;
}