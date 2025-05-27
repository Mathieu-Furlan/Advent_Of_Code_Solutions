#include <fstream>
#include <string>
#include <iostream>

int main(){
    char ch;
    int res{0};
    int individualValue{0};
    std::fstream fin("input", std::fstream::in);
    while(fin >> std::noskipws >> ch){
        if(ch != 44 && ch != 10){
            individualValue += ch;
            std::cout << "char " << ch << "\n";
            std::cout << "indivVal " << individualValue << "\n";
            individualValue *= 17;
            individualValue = individualValue % 256;
            individualValue;
        }
        else{
            std::cout << "sequElem" << individualValue << "\n";
            res += individualValue;
            individualValue = 0;
        }
    }
    res += individualValue;
    std::cout << res << "\n";
    return res;
}