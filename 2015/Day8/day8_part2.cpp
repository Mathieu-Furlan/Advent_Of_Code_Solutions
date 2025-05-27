#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int code{0};
    int encoded{0};
    while(getline(file, s)){
        code++;
        encoded += 3;
        for(int i = 1; i <= s.length() - 2; i++){
            if(s[i] == 92){
                if(s[i + 1] == 92 || s[i + 1] == 34){
                    code += 2;
                    encoded += 4;
                    i++;
                }
                else if(s[i + 1] == 'x'){
                    code += 4;
                    encoded += 5;
                    i += 3;
                }
            }
        }
        code++;
        encoded += 3;
    }
    std::cout << encoded - code << "\n";
    return encoded - code;
}