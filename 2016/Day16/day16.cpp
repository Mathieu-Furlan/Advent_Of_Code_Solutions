#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

int main(){
    const int SIZE{272};
    std::string a{"10001110011110000"};
    while(a.length() < SIZE){
        std::string b{a};
        std::reverse(b.begin(), b.end());
        for(int i = 0; i < b.length(); i++){
            b[i] ^= 1;
        }
        a += '0';
        a += b; 
    }
    a = a.substr(0, SIZE);
    while(a.length() % 2 == 0){
        std::string next;
        for(int i = 0; i < a.length(); i = i + 2){
            if(a[i] == a[i + 1]){
                next += '1';
            }
            else next += '0';
        }
        a = next;
    }
    std::cout << a << "\n";
    return 0;
}